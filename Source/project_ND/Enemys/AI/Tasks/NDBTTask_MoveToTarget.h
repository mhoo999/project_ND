// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NDBTTask_MoveToTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDBTTask_MoveToTarget : public UBTTaskNode
{
	GENERATED_BODY()

	UNDBTTask_MoveToTarget();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
