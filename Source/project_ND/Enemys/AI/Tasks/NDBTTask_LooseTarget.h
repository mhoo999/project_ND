// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NDBTTask_LooseTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDBTTask_LooseTarget : public UBTTaskNode
{
	GENERATED_BODY()

	UNDBTTask_LooseTarget();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
