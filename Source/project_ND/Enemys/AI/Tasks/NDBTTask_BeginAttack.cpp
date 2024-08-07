// Copyright by project_ND


#include "NDBTTask_BeginAttack.h"

#include "AIController.h"
#include "project_ND/Enemys/NDZombieBase.h"

UNDBTTask_BeginAttack::UNDBTTask_BeginAttack()
{
	NodeName = "change state Begin attack";
}

EBTNodeResult::Type UNDBTTask_BeginAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANDZombieBase* Zombie = Cast<ANDZombieBase>(OwnerComp.GetAIOwner()->GetPawn());

	if (Zombie)
	{
		Zombie->ChangeStateAttack();
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
