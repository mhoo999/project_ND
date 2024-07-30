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
	if (!AIController)
	{
		return Super::ExecuteTask(OwnerComp, NodeMemory);
	}

	const UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
	if (!BlackboardComponent)
	{
		return Super::ExecuteTask(OwnerComp, NodeMemory);
	}

	const FName TargetKey = "Target";
	if (AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetKey)))
	{
		AIController->MoveToActor(Target);
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
