// Copyright by project_ND


#include "NDAnimPlayer.h"
#include "NDPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


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

	// Direction = Player->GetVelocity().Size2D();

	Velocity = Player->GetCharacterMovement()->Velocity;

	bIsFalling = Player->GetCharacterMovement()->IsFalling();

	bIsCrouch = Player->GetIsCrouched();

	FRotator BaseLotator = Player->GetActorRotation();
	Direction = CalculateDirection(Velocity, BaseLotator);

}
