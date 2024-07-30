// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NDZombieAnim.generated.h"

class ANDZombieBase;
/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDZombieAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animation")
	float Speed;

	UPROPERTY()
	ANDZombieBase* ZombieBase;

	UPROPERTY(EditDefaultsOnly, Category="Anims")
	UAnimMontage* AttackAnim;

	UFUNCTION()
	void AnimNotify_StartATK();

	UFUNCTION()
	void AnimNotify_EndATK();
};
