// Copyright by project_ND


#include "NDPlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "project_ND/Core/Components/NDInputComponent.h"
#include "project_ND/Core/Components/NDStatComponent.h"
#include "project_ND/Enemys/NDZombieBase.h"


//class ANDWeapon;
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	PCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	//Camera->SetupAttachment(CapsuleComponent);
	SpringArm->SetupAttachment(RootComponent);
	PCamera->SetupAttachment(SpringArm);
	PCamera->bUsePawnControlRotation = true; 
	//Camera->Setup

	//Target = cast<ANDZombieBase>();

	MyInputComponent = CreateDefaultSubobject<UNDInputComponent>("MyInputComponent");
	//MyInputComponent = Cast<UNDInputComponent>(GetComponentByClass(UNDInputComponent::StaticClass()));

	StatComponent->SetCurHP(100)->SetDamage(40);

	//Target = Cast<ANDZombieBase>();
	//Target->TakeDamage(40);
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

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//bUseControllerRotationYaw = false;
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
		EnhancedInputComponent->BindAction(MyInputComponent->CrouchAction, ETriggerEvent::Started, this, &APlayerCharacter::CrouchEnd);

		EnhancedInputComponent->BindAction(MyInputComponent->SprintAction, ETriggerEvent::Ongoing  , this, &APlayerCharacter::SprintStart);
		EnhancedInputComponent->BindAction(MyInputComponent->SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::SprintEnd);

		EnhancedInputComponent->BindAction(MyInputComponent->ChangeWeaponAction, ETriggerEvent::Started, this, &APlayerCharacter::OnFlashLightKey);
		EnhancedInputComponent->BindAction(MyInputComponent->EquipBluntWeapon, ETriggerEvent::Started, this, &APlayerCharacter::OnBluntWeaponKey);

		EnhancedInputComponent->BindAction(MyInputComponent->AttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::OnAttack);

		EnhancedInputComponent->BindAction(MyInputComponent->ThrowAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Throw);
		
		EnhancedInputComponent->BindAction(MyInputComponent->ThrowAction, ETriggerEvent::Triggered, this, &APlayerCharacter::FlashLightOn);


		//UE_LOG(,)
	}
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

	if (StatComponent->bIsWalking)
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
	if (CurWeaponType != EWeaponType::UNARMED || bIsCrouched)
		return;

	ACharacter::Jump();
}

void APlayerCharacter::CrouchStart(const FInputActionValue& Value)
{
	bIsCrouched = !bIsCrouched;

	if (bIsCrouched)
	{
		GetCharacterMovement()->MaxWalkSpeed = 350.0f;
	
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}

}

void APlayerCharacter::CrouchEnd(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void APlayerCharacter::SprintStart()
{
	StatComponent->bIsWalking = false;

	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
}

void APlayerCharacter::SprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void APlayerCharacter::OnFlashLightKey(const FInputActionValue& Value)
{
	ChangeWeapon(EWeaponType::FLASHLIGHT);
}

void APlayerCharacter::OnBluntWeaponKey(const FInputActionValue& Value)
{
	ChangeWeapon(EWeaponType::BLUNTWEAPON);
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
	Weapons[NextWeaponType]->AttachToHand(GetMesh());

	NextWeaponType = EWeaponType::UNARMED;

	if (CurWeaponType == EWeaponType::UNARMED)
		StrafeOff();
	else
		StrafeOn();
}

void APlayerCharacter::OnSheathEnd()
{
	GetCurrentWeapon()->AttachToHolster(GetMesh());

	if (NextWeaponType == EWeaponType::UNARMED)
	{
		CurWeaponType = EWeaponType::UNARMED;
		StrafeOff();
	}
	else
	{
		CurWeaponType = NextWeaponType;

		PlayAnimMontage(GetCurrentWeapon()->GetDrawMontage());
	}
}

void APlayerCharacter::OnAttack()
{
	if (StatComponent->bIsAttacking)
		return;

	switch (CurWeaponType)
	{
	case EWeaponType::UNARMED:
		break;
	default:
		GetCurrentWeapon()->Attack();
		break;
	}
}

void APlayerCharacter::OnAttackBegin()
{
	StatComponent->bIsAttacking = true;

	GetCurrentWeapon()->GetBodyCollider()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCurrentWeapon()->GetBodyCollider()->bHiddenInGame = false;
}

void APlayerCharacter::OnAttackEnd()
{
	StatComponent->bIsAttacking = false;

	GetCurrentWeapon()->GetBodyCollider()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCurrentWeapon()->GetBodyCollider()->bHiddenInGame = true;
}

void APlayerCharacter::Throw()
{
}

void APlayerCharacter::FlashLightOn()
{
}





