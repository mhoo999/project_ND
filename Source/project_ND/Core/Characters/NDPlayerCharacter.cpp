// Copyright by project_ND


#include "NDPlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SkeletalMeshComponent.h"
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



//class ANDWeapon;
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	PCamera   = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));

	ProjectilStart = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectilStart"));
	ProjectilPath  = CreateDefaultSubobject<USplineComponent>(TEXT("ProjectilPath"));
	
	SpringArm->SetupAttachment(RootComponent);
	PCamera->SetupAttachment(SpringArm);
	PCamera->bUsePawnControlRotation = true;

	SpringArm->SetRelativeLocation(FVector(0.0f, 30.0f, 75.0f));

	ProjectilStart->SetupAttachment(RootComponent);
	 ProjectilPath->SetupAttachment(ProjectilStart);

	ZoomTimeline   = CreateDefaultSubobject<UTimelineComponent>(TEXT("ZoomTImeline"));
	CrouchTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("CrouchTimeline"));


	MyInputComponent = CreateDefaultSubobject<UNDInputComponent>(TEXT("MyInputComponent"));
	//MyInputComponent = Cast<UNDInputComponent>(GetComponentByClass(UNDInputComponent::StaticClass()));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
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

	OnPlayerDamaged.AddDynamic(this, &APlayerCharacter::HandlePlayerDamaged);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//bUseControllerRotationYaw = false;

	if (ZoomTimeline)
	{
		ZoomTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent 
		= Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(MyInputComponent->JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::OnJump);

		EnhancedInputComponent->BindAction(MyInputComponent->MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(MyInputComponent->LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(MyInputComponent->WalkAction, ETriggerEvent::Started  , this, &APlayerCharacter::Walk);

		EnhancedInputComponent->BindAction(MyInputComponent->CrouchAction, ETriggerEvent::Started, this, &APlayerCharacter::CrouchStart);

		EnhancedInputComponent->BindAction(MyInputComponent->SprintAction, ETriggerEvent::Ongoing  , this, &APlayerCharacter::SprintStart);
		EnhancedInputComponent->BindAction(MyInputComponent->SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::SprintEnd);

		EnhancedInputComponent->BindAction(MyInputComponent->ChangeFirstSlot, ETriggerEvent::Started, this, &APlayerCharacter::ChangeFirstSlotItem);
		EnhancedInputComponent->BindAction(MyInputComponent->ChangeSecondSlot, ETriggerEvent::Started, this, &APlayerCharacter::ChangeSecondSlotItem);
		EnhancedInputComponent->BindAction(MyInputComponent->ChangeThirdSlot, ETriggerEvent::Started, this, &APlayerCharacter::ChangeThirdSlotItem);
		
		EnhancedInputComponent->BindAction(MyInputComponent->ChangeWeaponAction, ETriggerEvent::Started, this, &APlayerCharacter::OnFlashLightKey);

		EnhancedInputComponent->BindAction(MyInputComponent->AttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::OnAttack);
		EnhancedInputComponent->BindAction(MyInputComponent->AttackAction, ETriggerEvent::Started  , this, &APlayerCharacter::OnAttackPressed);
		EnhancedInputComponent->BindAction(MyInputComponent->AttackAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnAttackReleased);
		
		EnhancedInputComponent->BindAction(MyInputComponent->ChangeThirdSlot, ETriggerEvent::Triggered, this, &APlayerCharacter::FlashLightOn);


		//UE_LOG(,)
	}
}

void APlayerCharacter::TakeDamage(float DamageAmount, AActor* Attacker, FHitResult HitResult)
{
	Super::TakeDamage(DamageAmount, Attacker, HitResult);
}

void APlayerCharacter::Move(const FInputActionValue& Value)
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

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput  (LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Walk(const FInputActionValue& Value)
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

void APlayerCharacter::OnJump()
{
	if (CurPickUpObjectType != EWeaponType::UNARMED || bIsCrouched)
		return;

	ACharacter::Jump();
}

void APlayerCharacter::CrouchStart(const FInputActionValue& Value)
{
	bIsCrouched = !bIsCrouched;

	if (bIsCrouched)
	{
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;

		//UE_LOG(LogTemp, Warning, TEXT("Target Arm Length : %f"), SpringArm->TargetArmLength);

		if (CrouchTimeline)
		{
			CrouchTimeline->Play();
		}

		//UE_LOG(LogTemp, Warning, TEXT("Target Arm Length : %f"), SpringArm->TargetArmLength);
		
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

void APlayerCharacter::HandleCrouchProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(DefaulCrouchLocation, CrouchedLocation, Value);
	SpringArm->SetRelativeLocation(NewLocation);
}

void APlayerCharacter::HandleZoomProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(DefaultCameraLocation, ZoomOutLocation, Value);
	NewLocation.Y = DefaultCameraLocation.Y;
	SpringArm->SetRelativeLocation(NewLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Zoom Value: %f, NewLocation: %s"), Value, *NewLocation.ToString());
}

void APlayerCharacter::SprintStart()
{
	StatComponent->bIsWalking = false;

	if (ZoomTimeline)
	{
		GetCharacterMovement()->MaxWalkSpeed = 800.0f;
		ZoomTimeline->Play();

		//UE_LOG(LogTemp, Warning, TEXT("ZoomTimeline Play"));
	}
}

void APlayerCharacter::SprintEnd()
{
	if (ZoomTimeline)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		ZoomTimeline->Reverse();

		//UE_LOG(LogTemp, Warning, TEXT("ZoomTimeline Reverse"));
	}
}

void APlayerCharacter::OnFlashLightKey(const FInputActionValue& Value)
{
	ChangeWeapon(EWeaponType::FLASHLIGHT);
}

void APlayerCharacter::ChangeFirstSlotItem(const FInputActionValue& Value)
{
	if (EquipComponent->GetFirstSlot() == nullptr && bIsSwap)
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
			NextEquipmentItem = EquipComponent->GetFirstSlot();
			NextEquipmentSLot = EEquipment::FIRSTSLOT;
			
			AnimInstance->Montage_Play(CurrentEquipmentItem->GetSheathMontage());
		}
	}
}

void APlayerCharacter::ChangeSecondSlotItem(const FInputActionValue& Value)
{
	if (EquipComponent->GetSecondSlot() == nullptr && bIsSwap)
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
			NextEquipmentItem = EquipComponent->GetSecondSlot();
			NextEquipmentSLot = EEquipment::SECONDSLOT;
			
			AnimInstance->Montage_Play(CurrentEquipmentItem->GetSheathMontage());
		}
	}
}

void APlayerCharacter::ChangeThirdSlotItem(const FInputActionValue& Value)
{
	if (EquipComponent->GetThirdSlot() == nullptr && bIsSwap)
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
			NextEquipmentItem = EquipComponent->GetThirdSlot();
			NextEquipmentSLot = EEquipment::THIRDSLOT;
			
			AnimInstance->Montage_Play(CurrentEquipmentItem->GetSheathMontage());
		}
	}
}

void APlayerCharacter::StrafeOn()
{
	//bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void APlayerCharacter::StrafeOff()
{
	//bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void APlayerCharacter::OnDrawEnd()
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
	bIsSwap = false;
}

void APlayerCharacter::OnSheathEnd()
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

void APlayerCharacter::FootStepSound()
{
	FVector NoiseLocation = this->GetActorLocation();
	UAISense_Hearing::ReportNoiseEvent(GetWorld(), NoiseLocation, 1.0f, this);
	UE_LOG(LogTemp, Warning, TEXT("Walk"));
}

void APlayerCharacter::OnAttack()
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
		Cast<ANDWeaponBase>(CurrentEquipmentItem)->Attack();
	}
	else if (CurrentEquipmentSlot == EEquipment::THIRDSLOT)
	{
		BPThrowable();
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
	// 		////OnMontageEndeDelegate.BindUObject(this, &APlayerCharacter::OnMontageEnded);
	// 		////PlayAnimMontage()->Montage_SetEndelegate(OnMontageEndeDelegate, GetSheathMontage());
	//
	// 	}	
	// 	break;
	// default:
	// 	Cast<ANDWeaponBase>(CurrentEquipmentItem)->Attack();
	// 	break;
	// }
}

void APlayerCharacter::OnAttackPressed()
{
	//if (StatComponent->bIsAttacking)
	//	return;

	//switch (CurPickUpObjectType)
	//{
	//case EWeaponType::UNARMED:
	//	break;
	//case EWeaponType::THORWABLE:
	//	//Cast<ANDWeaponBase>(GetCurrentPickUpObject())->Attack();
	//	//Throwables();
	//	break;
	//default:
	//	break;
	//}

	/*if (StatComponent->bIsAttacking)
		return;
	
	if (CurPickUpObjectType == EWeaponType::THORWABLE)
	{
		StatComponent->bIsAttacking = true;
	}*/
	//else (CurPickUpObjectType == EWeaponType::BLUNTWEAPON)
	//	OnAttack();
	
		
		

	/*GetWorldTimerManager().SetTimer(AttackHoldTimerHandle, this, &AYourCharacter::PerformAimedAttack, HoldThreshold, false); */

}

void APlayerCharacter::OnAttackReleased()
{
	/*GetWorldTimerManager().ClearTimer(AttackHoldTimerHandle);

	if (bIsAttacking)
	{
		PerformSingleAttack();
	}

	bIsAttacking = false;*/
}

void APlayerCharacter::OnAttackBegin()
{
	StatComponent->bIsAttacking = true;

	CurrentEquipmentItem->GetBodyCollider()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CurrentEquipmentItem->GetBodyCollider()->bHiddenInGame = false;
	/*Cast<ANDWeaponBase>(GetCurrentWeapon())->GetBodyCollider()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Cast<ANDWeaponBase>(GetCurrentWeapon())->GetBodyCollider()->bHiddenInGame = false;*/

}

void APlayerCharacter::OnAttackEnd()
{
	StatComponent->bIsAttacking = false;

	CurrentEquipmentItem->GetBodyCollider()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CurrentEquipmentItem->GetBodyCollider()->bHiddenInGame = true;
	/*Cast<ANDWeaponBase>(GetCurrentWeapon())->GetBodyCollider()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Cast<ANDWeaponBase>(GetCurrentWeapon())->GetBodyCollider()->bHiddenInGame = true;*/

}

void APlayerCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// ChangeWeapon(EWeaponType::UNARMED);
}

void APlayerCharacter::HandlePlayerDamaged()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController && MyCameraShakeClass)
	{
		PlayerController->ClientStartCameraShake(MyCameraShakeClass);
	}
}



void APlayerCharacter::FlashLightOn()
{
	//bool FlasLight = true;


	//if (FlasLight) 
	//{
	//	// code
	//	

	//	FlasLight = false;
	//}
	//else 
	//{
	//	// code
	//	FlasLight = true;
	//}



	//PlayAnimMontage(UAnimMontage* AnimMontage, float InPlayRate = 1.0f, FName = "Standing_Taunt_Chest_fix_Montage");
}





