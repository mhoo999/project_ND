// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NDBTTask_PlayRandomAnimation.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDBTTask_PlayRandomAnimation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UNDBTTask_PlayRandomAnimation();

private:
	UPROPERTY(EditAnywhere, Category="Animation")
	TArray<UAnimSequence*> Montages;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
