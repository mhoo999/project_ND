// Copyright by project_ND


#include "NDBTTask_CleanBlackBoard.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UNDBTTask_CleanBlackBoard::UNDBTTask_CleanBlackBoard()
{
	NodeName = "Clean black board";
}

EBTNodeResult::Type UNDBTTask_CleanBlackBoard::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	
	for (const FName& ValueName : NodeToDelete)
	{
		BlackboardComponent->ClearValue(ValueName);
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
