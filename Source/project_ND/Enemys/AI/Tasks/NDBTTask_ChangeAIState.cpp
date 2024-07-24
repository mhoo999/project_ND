// Copyright by project_ND


#include "NDBTTask_ChangeAIState.h"

#include "AIController.h"
#include "project_ND/Core/Enemys/NDAIController.h"

UNDBTTask_ChangeAIState::UNDBTTask_ChangeAIState()
{
	NodeName = "Change ai state";
}

EBTNodeResult::Type UNDBTTask_ChangeAIState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANDAIController* AIController = Cast<ANDAIController>(OwnerComp.GetAIOwner());

	AIController->SetAIState(NewState);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
