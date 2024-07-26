// Copyright by project_ND


#include "NDBTTask_LooseTarget.h"

#include "project_ND/Core/Enemys/NDAIController.h"
#include "project_ND/Enemys/NDZombieBase.h"

UNDBTTask_LooseTarget::UNDBTTask_LooseTarget()
{
	NodeName = "Loose Target";
}

EBTNodeResult::Type UNDBTTask_LooseTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANDAIController* AIController = Cast<ANDAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return Super::ExecuteTask(OwnerComp, NodeMemory);
	}

	AIController->ToggleBeChasePlayer();
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
