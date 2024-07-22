// Copyright by project_ND


#include "Enemys/AI/Tasks/BTTask_ChangeAIState.h"

#include "AIController.h"
#include "Core/Enemys/NDAIController.h"

UBTTask_ChangeAIState::UBTTask_ChangeAIState()
{
	NodeName = "Change ai state";
}

EBTNodeResult::Type UBTTask_ChangeAIState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANDAIController* AIController = Cast<ANDAIController>(OwnerComp.GetAIOwner());

	AIController->SetAIState(NewState);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
