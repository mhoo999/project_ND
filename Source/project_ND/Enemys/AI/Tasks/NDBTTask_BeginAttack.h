// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NDBTTask_BeginAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDBTTask_BeginAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UNDBTTask_BeginAttack();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
