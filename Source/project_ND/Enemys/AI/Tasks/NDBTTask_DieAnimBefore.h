// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NDBTTask_DieAnimBefore.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDBTTask_DieAnimBefore : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UNDBTTask_DieAnimBefore();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
