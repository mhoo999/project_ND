// Copyright by project_ND


#include "NDBTTask_SetLocation.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UNDBTTask_SetLocation::UNDBTTask_SetLocation()
{
	NodeName = "Set location";
}

EBTNodeResult::Type UNDBTTask_SetLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	if (!BlackboardComponent)
	{
		return Super::ExecuteTask(OwnerComp, NodeMemory);
	}
	
	const AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject("Target"));
	if (!Target)
	{
		return Super::ExecuteTask(OwnerComp, NodeMemory);
	}

	BlackboardComponent->SetValueAsVector("Destination", Target->GetActorLocation());
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
