// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NDPlayerCharacter.h"
#include "NDAnimPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDAnimPlayer : public UAnimInstance
{
	GENERATED_BODY()
	
	UNDAnimPlayer();

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Direction = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Velocity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsFalling = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsCrouch = false; 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsThrowring = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class APlayerCharacter* Player = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EWeaponType CurWeapon;
};
