// Copyright by project_ND


#include "NDBTTask_MoveToTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UNDBTTask_MoveToTarget::UNDBTTask_MoveToTarget()
{
	NodeName = "Move to target";
}

EBTNodeResult::Type UNDBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();

	if (BlackboardComponent)
	{
		AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject("Target"));
		
		if (Target)
		{
			AIController->MoveToActor(Target);
		}
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
