// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NDBTTask_SetLocation.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDBTTask_SetLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UNDBTTask_SetLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
