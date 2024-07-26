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
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
	const AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject("Target"));

	BlackboardComponent->SetValueAsVector("Destination", Target->GetActorLocation());
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
