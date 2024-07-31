// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NDBTTask_ZombieAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDBTTask_ZombieAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UNDBTTask_ZombieAttack();

private:
	// virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> MyOwnerComp;
	
	FTimerHandle TimerHandle;

};
