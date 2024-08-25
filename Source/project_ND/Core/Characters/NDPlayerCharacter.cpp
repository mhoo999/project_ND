// Copyright by project_ND


#include "NDPlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "project_ND/Core/Components/NDEquipComponent.h"
#include "project_ND/Core/Components/NDInputComponent.h"
#include "project_ND/Core/Components/NDStatComponent.h"
#include "project_ND/Enemys/NDZombieBase.h"
#include "Perception/AISense_Hearing.h"
#include "Sound/SoundBase.h"
#include "project_ND/PickUpObject/Weapons/NDRevolverBase.h"
#include "DrawDebugHelpers.h"



//class ANDWeapon;
// Sets default values
ANDPlayerCharacter::ANDPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	PCamera   = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	AimCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("AimCamera"));
	FlahsSpringArm  = CreateDefaultSubobject<USpringArmComponent>(TEXT("FlashSpringArm"));
	FlashLightSpot = CreateDefaultSubobject<USpotLightComponent>(TEXT("FlashLightSport"));


	ProjectilStart = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectilStart"));
	ProjectilPath  = CreateDefaultSubobject<USplineComponent>(TEXT("ProjectilPath"));
	
	SpringArm->SetupAttachment(RootComponent);
	PCamera->SetupAttachment(SpringArm);
	PCamera->bUsePawnControlRotation = true;
	AimCamera->SetupAttachment(RootComponent);
	FlahsSpringArm->SetupAttachment(RootComponent);
	FlashLightSpot->SetupAttachment(FlahsSpringArm);
	
	FlashLightSpot->IsVisible();

	SpringArm->SetRelativeLocation(FVector(0.0f, 30.0f, 75.0f));

	ProjectilStart->SetupAttachment(RootComponent);
	 ProjectilPath->SetupAttachment(ProjectilStart);

	ZoomTimeline   = CreateDefaultSubobject<UTimelineComponent>(TEXT("ZoomTImeline"));
	CrouchTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("CrouchTimeline"));


	MyInputComponent = CreateDefaultSubobject<UNDInputComponent>(TEXT("MyInputComponent"));

}

// Called when the game starts or when spawned
void ANDPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (IsValid(SubSystem))
		{
			SubSystem->AddMappingContext(MyInputComponent->MappingContext, 0);
		}
	}

	DefaultCameraLocation = SpringArm->GetRelativeLocation();
	ZoomOutLocation = DefaultCameraLocation + FVector(-50.0f, 0.0f, 0.0f);

	if (ZoomCurve)
	{
		FOnTimelineFloat TimelineCallback;
		TimelineCallback.BindUFunction(this, FName("HandleZoomProgress"));

		ZoomTimeline->AddInterpFloat(ZoomCurve, TimelineCallback);
	}


	//Crouched
	DefaulCrouchLocation = SpringArm->GetRelativeLocation();
	CrouchedLocation = DefaulCrouchLocation + FVector(0.0f, 0.0f, -50.0f);


	if (ZoomCurve)
	{
		FOnTimelineFloat TimelineCallback;
		TimelineCallback.BindUFunction(this, FName("HandleCrouchProgress"));

		CrouchTimeline->AddInterpFloat(ZoomCurve, TimelineCallback);
	}

	OnPlayerDamaged.AddDynamic(this, &ANDPlayerCharacter::HandlePlayerDamaged);

	AimCamera->SetActive(false);

	bIsFlashLightOn = false;
	FlashLightSpot->SetVisibility(false);
}

// Called every frame
void ANDPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//bUseControllerRotationYaw = false;

	if (ZoomTimeline)
	{
		ZoomTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);
	}

	if (bIsAttackTrace)
	{
		PerformHandSphereTraces();
	}
}

// Called to bind functionality to input
void ANDPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent 
		= Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(MyInputComponent->JumpAction, ETriggerEvent::Started, this, &ANDPlayerCharacter::OnJump);

		EnhancedInputComponent->BindAction(MyInputComponent->MoveAction, ETriggerEvent::Triggered, this, &ANDPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(MyInputComponent->LookAction, ETriggerEvent::Triggered, this, &ANDPlayerCharacter::Look);
		EnhancedInputComponent->BindAction(MyInputComponent->WalkAction, ETriggerEvent::Started  , this, &ANDPlayerCharacter::Walk);

		EnhancedInputComponent->BindAction(MyInputComponent->CrouchAction, ETriggerEvent::Started, this, &ANDPlayerCharacter::CrouchStart);

		EnhancedInputComponent->BindAction(MyInputComponent->SprintAction, ETriggerEvent::Ongoing  , this, &ANDPlayerCharacter::SprintStart);
		EnhancedInputComponent->BindAction(MyInputComponent->SprintAction, ETriggerEvent::Completed, this, &ANDPlayerCharacter::SprintEnd);

		EnhancedInputComponent->BindAction(MyInputComponent->ChangeFirstSlot , ETriggerEvent::Started, this, &ANDPlayerCharacter::ChangeFirstSlotItem );
		EnhancedInputComponent->BindAction(MyInputComponent->ChangeSecondSlot, ETriggerEvent::Started, this, &ANDPlayerCharacter::ChangeSecondSlotItem);
		EnhancedInputComponent->BindAction(MyInputComponent->ChangeThirdSlot , ETriggerEvent::Started, this, &ANDPlayerCharacter::ChangeThirdSlotItem );
		
		EnhancedInputComponent->BindAction(MyInputComponent->ChangeWeaponAction, ETriggerEvent::Started, this, &ANDPlayerCharacter::OnFlashLightKey);

		EnhancedInputComponent->BindAction(MyInputComponent->AttackAction, ETriggerEvent::Triggered, this, &ANDPlayerCharacter::OnAttack);

		EnhancedInputComponent->BindAction(MyInputComponent->ChangeCameraAction, ETriggerEvent::Ongoing  , this, &ANDPlayerCharacter::ChangeToAimCamera );
		EnhancedInputComponent->BindAction(MyInputComponent->ChangeCameraAction, ETriggerEvent::Completed, this, &ANDPlayerCharacter::ChangeToMainCamera);
		
		EnhancedInputComponent->BindAction(MyInputComponent->FlashLightOnAction, ETriggerEvent::Started, this, &ANDPlayerCharacter::FlashLightOn);

		EnhancedInputComponent->BindAction(MyInputComponent->ReloadAction, ETriggerEvent::Started, this, &ANDPlayerCharacter::RevolverReload);

	}
}

void ANDPlayerCharacter::TakeDamage(float DamageAmount, AActor* Attacker, FHitResult HitResult)
{
	Super::TakeDamage(DamageAmount, Attacker, HitResult);
}

void ANDPlayerCharacter::Move(const FInputActionValue& Value)
{
	//if (CurWeaponType != EWeaponType::UNARMED)
	//	bUseControllerRotationYaw = true;

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();

		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector	RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(  RightDirection, MovementVector.X);
	}

	//bUseControllerRotationYaw = false;
}

void ANDPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput  (LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ANDPlayerCharacter::Walk(const FInputActionValue& Value)
{
	StatComponent->bIsWalking = !StatComponent->bIsWalking;

	float Speed = GetVelocity().Size();

	
	if (Speed > 200.0f || StatComponent->bIsWalking)
	{
		GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
	
}

void ANDPlayerCharacter::OnJump()
{
	if (CurPickUpObjectType != EWeaponType::UNARMED || bIsCrouched)
		return;

	ACharacter::Jump();
}

void ANDPlayerCharacter::CrouchStart(const FInputActionValue& Value)
{
	bIsCrouched = !bIsCrouched;

	if (bIsCrouched)
	{
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;

		if (CrouchTimeline)
		{
			CrouchTimeline->Play();
		}
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;

		if (CrouchTimeline)
		{
			CrouchTimeline->Reverse();
		}
	}
}

void ANDPlayerCharacter::HandleCrouchProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(DefaulCrouchLocation, CrouchedLocation, Value);
	SpringArm->SetRelativeLocation(NewLocation);
}

void ANDPlayerCharacter::HandleZoomProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(DefaultCameraLocation, ZoomOutLocation, Value);
	NewLocation.Y = DefaultCameraLocation.Y;
	SpringArm->SetRelativeLocation(NewLocation);
}

void ANDPlayerCharacter::SprintStart()
{
	StatComponent->bIsWalking = false;

	if (ZoomTimeline)
	{
		GetCharacterMovement()->MaxWalkSpeed = 800.0f;
		ZoomTimeline->Play();
	}
}

void ANDPlayerCharacter::SprintEnd()
{
	if (ZoomTimeline)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		ZoomTimeline->Reverse();
	}
}

void ANDPlayerCharacter::OnFlashLightKey(const FInputActionValue& Value)
{
	ChangeWeapon(EWeaponType::FLASHLIGHT);
}

void ANDPlayerCharacter::ChangeFirstSlotItem(const FInputActionValue& Value)
{
	if (EquipComponent->GetFirstSlot() == nullptr || bIsSwap)
	{
		return;
	}

	bIsSwap = true;
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		if (CurrentEquipmentSlot == EEquipment::UNARMED)
		{
			CurrentEquipmentItem = EquipComponent->GetFirstSlot();
			CurrentEquipmentSlot = EEquipment::FIRSTSLOT;
			
			AnimInstance->Montage_Play(CurrentEquipmentItem->GetDrawMontage());
		}
		else
		{
			//bHasWeaponEquip = true;

			NextEquipmentItem = EquipComponent->GetFirstSlot();
			NextEquipmentSLot = EEquipment::FIRSTSLOT;
			
			AnimInstance->Montage_Play(CurrentEquipmentItem->GetSheathMontage());
		}
	}
}

void ANDPlayerCharacter::ChangeSecondSlotItem(const FInputActionValue& Value)
{
	if (EquipComponent->GetSecondSlot() == nullptr || bIsSwap)
	{
		return;
	}

	bIsSwap = true;
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		if (CurrentEquipmentSlot == EEquipment::UNARMED)
		{
			CurrentEquipmentItem = EquipComponent->GetSecondSlot();
			CurrentEquipmentSlot = EEquipment::SECONDSLOT;
			
			AnimInstance->Montage_Play(CurrentEquipmentItem->GetDrawMontage());
		}
		else
		{
			//bHasWeaponEquip = true;

			NextEquipmentItem = EquipComponent->GetSecondSlot();
			NextEquipmentSLot = EEquipment::SECONDSLOT;
			
			AnimInstance->Montage_Play(CurrentEquipmentItem->GetSheathMontage());
		}
	}
}

void ANDPlayerCharacter::ChangeThirdSlotItem(const FInputActionValue& Value)
{
	if (EquipComponent->GetThirdSlot() == nullptr || bIsSwap)
	{
		return;
	}
	
	bIsSwap = true;
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		if (CurrentEquipmentSlot == EEquipment::UNARMED)
		{
			CurrentEquipmentItem = EquipComponent->GetThirdSlot();
			CurrentEquipmentSlot = EEquipment::THIRDSLOT;
			
			AnimInstance->Montage_Play(CurrentEquipmentItem->GetDrawMontage());
		}
		else
		{
			//bHasWeaponEquip = false;
			bIsSwap = false;

			if (CurrentEquipmentSlot == EEquipment::THIRDSLOT)
			{
				
				CurrentEquipmentItem = nullptr;
				CurrentEquipmentSlot = EEquipment::UNARMED;
			}
			else
			{
				NextEquipmentItem = EquipComponent->GetThirdSlot();
				NextEquipmentSLot = EEquipment::THIRDSLOT;
				AnimInstance->Montage_Play(CurrentEquipmentItem->GetSheathMontage());

				//NextEquipmentItem = EquipComponent->GetThirdSlot();
				//NextEquipmentSLot = EEquipment::THIRDSLOT;

				//AnimInstance->Montage_Play(CurrentEquipmentItem->GetSheathMontage());
			}
		}
	}
}

void ANDPlayerCharacter::StrafeOn()
{
	//bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ANDPlayerCharacter::StrafeOff()
{
	//bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ANDPlayerCharacter::OnDrawEnd()
{
	// PickUpObjects[NextPickUpObjectType]->AttachToHand(GetMesh());
	//
	// NextPickUpObjectType = EWeaponType::UNARMED;
	//
	// if (CurPickUpObjectType == EWeaponType::UNARMED)
	// 	StrafeOff();
	// else
	// 	StrafeOn();

	CurrentEquipmentItem->AttachToHand(GetMesh());

	const float WeaponDamage = CurrentEquipmentItem->GetDamageAmount();
	if (StatComponent)
	{
		StatComponent->SetDamage(StatComponent->Damage + WeaponDamage);
	}
	
	bIsSwap = false;
}

void ANDPlayerCharacter::OnSheathEnd()
{
	// GetCurrentPickUpObject()->AttachToHolster(GetMesh());
	//
	// if (NextPickUpObjectType == EWeaponType::UNARMED)
	// {
	// 	CurPickUpObjectType = EWeaponType::UNARMED;
	// 	StrafeOff();
	// }
	// else
	// {
	// 	CurPickUpObjectType = NextPickUpObjectType;
	//
	// 	PlayAnimMontage(GetCurrentPickUpObject()->GetDrawMontage());
	// }

	CurrentEquipmentItem->AttachToHolster(GetMesh());

	const float WeaponDamage = CurrentEquipmentItem->GetDamageAmount();
	if (StatComponent)
	{
		StatComponent->SetDamage(StatComponent->Damage - WeaponDamage);
	}

	if (NextEquipmentItem && CurrentEquipmentSlot != NextEquipmentSLot)
	{
		CurrentEquipmentItem = NextEquipmentItem;
		CurrentEquipmentSlot = NextEquipmentSLot;

		PlayAnimMontage(CurrentEquipmentItem->GetDrawMontage());

		NextEquipmentItem = nullptr;
		NextEquipmentSLot = EEquipment::UNARMED;
	}
	else
	{
		CurrentEquipmentItem = nullptr;
		CurrentEquipmentSlot = EEquipment::UNARMED;
		bIsSwap = false;
	}
}

void ANDPlayerCharacter::FootStepSound()
{
	FVector NoiseLocation = this->GetActorLocation();
	UAISense_Hearing::ReportNoiseEvent(GetWorld(), NoiseLocation, 1.0f, this);

	if (StepSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, StepSound, GetActorLocation());
	}
}



void ANDPlayerCharacter::OnAttack()
{
	if (StatComponent->bIsAttacking)
	{
		return;
	}

	if (CurrentEquipmentSlot == EEquipment::FIRSTSLOT)
	{
		Cast<ANDWeaponBase>(CurrentEquipmentItem)->Attack();
	
	}
	else if (CurrentEquipmentSlot == EEquipment::SECONDSLOT)
	{
		//Cast<ANDWeaponBase>(CurrentEquipmentItem)->Attack();
		
		ANDRevolverBase* Revolver = Cast<ANDRevolverBase>(CurrentEquipmentItem);

		if (Revolver)
		{

			if (Revolver->GetCurBullets() <= 0)
			{
				Revolver->Reload();
			}
			else
			{
				Revolver->Attack();
				HandlePlayerDamaged();
			}
		}
		
	}
	else if (CurrentEquipmentSlot == EEquipment::THIRDSLOT)
	{
		BPThrowable();
		DefaultCameraLocation = SpringArm->GetRelativeLocation();
		SpringArm->SetRelativeLocation(FVector(50.0f, 50.0f, 80.0f));
		//bHasWeaponEquip = false;
	}

	// switch (CurrentEquipmentSlot)
	// {
	// case EEquipment::UNARMED:
	// 	break;
	// case EEquipment::THIRDSLOT:
	// 	if (CurrentEquipmentSlot == EEquipment::THIRDSLOT)
	// 	{
	// 		//PlayAnimMontage(GetCurrentPickUpObject()->GetSheathMontage());
	//
	// 		BPThrowable();
	// 		//OnMontageEnded(GetCurrentPickUpObject()->GetSheathMontage(), true);
	// 		////FOnMontageEnded OnMontageEndeDelegate;
	// 		////OnMontageEndeDelegate.BindUObject(this, &ANDPlayerCharacter::OnMontageEnded);
	// 		////PlayAnimMontage()->Montage_SetEndelegate(OnMontageEndeDelegate, GetSheathMontage());
	//
	// 	}	
	// 	break;
	// default:
	// 	Cast<ANDWeaponBase>(CurrentEquipmentItem)->Attack();
	// 	break;
	// }
}

void ANDPlayerCharacter::OnAttackBegin()
{
	StatComponent->bIsAttacking = true;

	CurrentEquipmentItem->OnAttackBegin(this);
}

void ANDPlayerCharacter::OnAttackEnd()
{
	StatComponent->bIsAttacking = false;

	if (CurrentEquipmentSlot == EEquipment::THIRDSLOT)
	{
		SpringArm->SetRelativeLocation(DefaultCameraLocation);
	}

	CurrentEquipmentItem->OnAttackEnd();
	
	/*if (bHasWeaponEquip)
	{
		CurrentEquipmentItem->OnAttackEnd();
		SpringArm->SetRelativeLocation(DefaultCameraLocation);
	}
	else
	{
		CurrentEquipmentItem = nullptr;
		CurrentEquipmentSlot = EEquipment::UNARMED;
	}*/


	/*Cast<ANDWeaponBase>(GetCurrentWeapon())->GetBodyCollider()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Cast<ANDWeaponBase>(GetCurrentWeapon())->GetBodyCollider()->bHiddenInGame = true;*/

}

void ANDPlayerCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// ChangeWeapon(EWeaponType::UNARMED);
}

void ANDPlayerCharacter::HandlePlayerDamaged()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController && MyCameraShakeClass)
	{
		PlayerController->ClientStartCameraShake(MyCameraShakeClass);
	}
}

void ANDPlayerCharacter::ChangeToMainCamera()
{
	if (CurrentEquipmentSlot != EEquipment::SECONDSLOT)
		return;

	PCamera->SetActive(true);
	AimCamera->SetActive(false);
}

void ANDPlayerCharacter::ChangeToAimCamera()
{
	if (CurrentEquipmentSlot != EEquipment::SECONDSLOT)
		return;

	PCamera->SetActive(false);
	AimCamera->SetActive(true);
	AimCamera->bUsePawnControlRotation = true;
}

void ANDPlayerCharacter::FlashLightOn()
{

	if (FlashLightMontage && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(FlashLightMontage))
	{
		PlayAnimMontage(FlashLightMontage);

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ANDPlayerCharacter::ToggleFlashLightVisibility, 1.0f, false);
	}

	FlashLightSpot->SetVisibility(bIsFlashLightOn);
	bIsFlashLightOn = !bIsFlashLightOn;
}

void ANDPlayerCharacter::ToggleFlashLightVisibility()
{
	UGameplayStatics::PlaySoundAtLocation(this, FlashSound, GetActorLocation());
	GetMesh()->GetAnimInstance()->Montage_Stop(0.0f, FlashLightMontage);

	bIsFlashLightOn = !bIsFlashLightOn;
}

void ANDPlayerCharacter::RevolverReload()
{
	if (CurrentEquipmentSlot == EEquipment::SECONDSLOT)
	{
		ANDRevolverBase* Revolver = Cast<ANDRevolverBase>(CurrentEquipmentItem);
		if (Revolver && !Revolver->IsReloading())
		{
			Revolver->Reload();
		}
	}
}

void ANDPlayerCharacter::ChangeState()
{
	bIsSwap = false;
}

void ANDPlayerCharacter::PerformHandSphereTraces()
{
	FVector StartLoc = TraceWeapon->GetItemMeshComponent()->GetSocketLocation(FName("TraceStart"));
	FVector EndLoc = TraceWeapon->GetItemMeshComponent()->GetSocketLocation(FName("TraceEnd"));
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(TraceWeapon);
	
	FHitResult HitResult;

	// DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 1.f, 0, 1.f);

	if (bool Hit = GetWorld()->SweepSingleByChannel(HitResult, StartLoc, EndLoc, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(20.f),CollisionParams))
	{
		bIsAttackTrace = false;
		if (ANDZombieBase* Zombie = Cast<ANDZombieBase>(HitResult.GetActor()))
		{
			Zombie->TakeDamage(StatComponent->GetDamage(), this, HitResult);
		}
	}
}

void ANDPlayerCharacter::StartBluntAttack(ANDPickUpObject* Item)
{
	bIsAttackTrace = true;
	TraceWeapon = Item;
}

void ANDPlayerCharacter::EndBluntAttack()
{
	bIsAttackTrace = false;
	TraceWeapon = nullptr;
}
