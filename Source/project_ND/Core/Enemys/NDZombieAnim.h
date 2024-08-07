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
	virtual void NativeBeginPlay() override;
	
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animation", meta=(AllowPrivateAccess))
	float Speed;

	UPROPERTY()
	ANDZombieBase* Zombie;

	UPROPERTY(EditDefaultsOnly, Category="Anims")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditDefaultsOnly, Category="Anims")
	UAnimMontage* DamagedAnim;

	void PlayDamagedAnim();
	
	UFUNCTION()
	void AnimNotify_StartAtk();

	UFUNCTION()
	void AnimNotify_EndAtk();

	UFUNCTION()
	void AnimNotify_ChangeStateIsAttack();

	void PlayZombieAttack();
	float GetZombieAttackPlayTime() const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animation", meta=(AllowPrivateAccess))
	bool bIsAttacking;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animation", meta=(AllowPrivateAccess))
	bool bIsDamaged;
	
	UFUNCTION()
	void AnimNotify_ToggleSuperArmor();

	UFUNCTION()
	void AnimNotify_ReActiveZombie();
};
