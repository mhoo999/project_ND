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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	ANDZombieBase* ZombieBase;
};
