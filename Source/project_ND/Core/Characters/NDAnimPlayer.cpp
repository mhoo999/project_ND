// Copyright by project_ND


#include "NDAnimPlayer.h"
#include "NDPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetArrayLibrary.h"



UNDAnimPlayer::UNDAnimPlayer()
{
}

void UNDAnimPlayer::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Player = Cast<APlayerCharacter>(TryGetPawnOwner());
}

void UNDAnimPlayer::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Player == nullptr)
		return;

	Speed = Player->GetVelocity().Size2D();

	Velocity = Player->GetCharacterMovement()->Velocity;

	bIsFalling = Player->GetCharacterMovement()->IsFalling();

	bIsCrouch = Player->GetIsCrouched();

	FRotator BaseRotator = Player->GetActorRotation();
	
	Direction = CalculateDirection(Velocity, BaseRotator);

	// CurWeapon = Player->GetCurPickUpObjectType();
	
	CurWeapon = Player->CurrentEquipmentSlot;

	//Direction

	//FRotator Rotation;
	//
	//if (Player->GetCurWeaponType() == EWeaponType::UNARMED)
	//	Rotation = Player->Controller->GetControlRotation();
	//else
	//	Rotation = Player->GetActorRotation();
	//
	//const FRotator YawRotation(0, Rotation.Yaw, 0);
	//
	//Direction = CalculateDirection(Player->GetVelocity().GetSafeNormal2D(), YawRotation);
	//
	//CurWeapon = Player->GetCurWeaponType();
}
