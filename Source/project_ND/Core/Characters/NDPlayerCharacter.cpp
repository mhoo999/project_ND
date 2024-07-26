// Copyright by project_ND


#include "NDPlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "/Project/project_ND/Source/project_ND/Core/Weapon/NDWeapon.h"
#include "/Project/project_ND/Source/project_ND/Component/NDInputComponent.h"

//class ANDWeapon;
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyInputComponent = CreateDefaultSubobject<UNDInputComponent>("MyInputComponent");

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

	// Spawn Weapon 

	for (auto& pair : WeaponClasses)
	{
		ANDWeapon* weapon = GetWorld()->SpawnActor<ANDWeapon>(pair.Value);

		weapon->Attach(GetMesh());

		Weapons.Add(pair.Key, weapon);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent 
		= Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(MyInputComponent->JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);

		EnhancedInputComponent->BindAction(MyInputComponent->MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(MyInputComponent->LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(MyInputComponent->WalkAction, ETriggerEvent::Started  , this, &APlayerCharacter::Walk);

		EnhancedInputComponent->BindAction(MyInputComponent->CrouchAction, ETriggerEvent::Started, this, &APlayerCharacter::CrouchStart);
		EnhancedInputComponent->BindAction(MyInputComponent->CrouchAction, ETriggerEvent::Started, this, &APlayerCharacter::CrouchEnd);

		EnhancedInputComponent->BindAction(MyInputComponent->SprintAction, ETriggerEvent::Ongoing  , this, &APlayerCharacter::SprintStart);
		EnhancedInputComponent->BindAction(MyInputComponent->SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::SprintEnd);

		EnhancedInputComponent->BindAction(MyInputComponent->ChangeWeaponAction, ETriggerEvent::Started, this, &APlayerCharacter::OnFlashLightKey);


		//UE_LOG(,)
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
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
	bIsWalking = !bIsWalking;

	if (bIsWalking)
	{
		GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
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
	bIsWalking = false;

	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
}

void APlayerCharacter::SprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void APlayerCharacter::OnFlashLightKey(const FInputActionValue& Value)
{
	FString string = Value.ToString();

	ChangeWeapon(EWeaponType::FLASHLIGHT);
}

void APlayerCharacter::ChangeWeapon(EWeaponType InWeaponType)
{
	if (InWeaponType == CurWeaponType)
		return;

	//Change Weapon

	LastWeaponType = CurWeaponType;
	 CurWeaponType =  InWeaponType;

	OnEquipEnd();
}

void APlayerCharacter::StrafeOn()
{
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void APlayerCharacter::StrafeOff()
{
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void APlayerCharacter::OnEquipEnd()
{
	if (CurWeaponType == EWeaponType::UNARMED)
		StrafeOff();
	else
		StrafeOn();
}





