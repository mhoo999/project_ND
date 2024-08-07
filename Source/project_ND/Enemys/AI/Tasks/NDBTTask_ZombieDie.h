// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NDBTTask_ZombieDie.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDBTTask_ZombieDie : public UBTTaskNode
{
	GENERATED_BODY()

	UNDBTTask_ZombieDie();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
