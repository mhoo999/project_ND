// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PlayRandomAnimation.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ND_API UBTTask_PlayRandomAnimation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_PlayRandomAnimation();

private:
	UPROPERTY(EditAnywhere, Category="Animation")
	TArray<UAnimSequence*> Montages;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
