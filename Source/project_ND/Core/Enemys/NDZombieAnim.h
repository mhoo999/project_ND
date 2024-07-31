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

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animation", meta=(AllowPrivateAccess))
	float Speed;

	UPROPERTY()
	ANDZombieBase* ZombieBase;

	UPROPERTY(EditDefaultsOnly, Category="Anims")
	UAnimMontage* AttackAnim;

	UFUNCTION()
	static void AnimNotify_StartAtk();

	UFUNCTION()
	static void AnimNotify_EndAtk();

public:
	void PlayZombieAttack();
	float GetZombieAttackPlayTime() const;
	
};
