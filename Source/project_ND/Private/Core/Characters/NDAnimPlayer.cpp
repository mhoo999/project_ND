// Copyright by project_ND


#include "Core/Characters/NDAnimPlayer.h"
#include "Core/Characters/NDPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	bIsFalling = Player->GetCharacterMovement()->IsFalling();

	bIsCrouch = Player->GetIsCrouched();

}
