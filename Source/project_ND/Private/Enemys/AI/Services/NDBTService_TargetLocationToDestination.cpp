// Copyright by project_ND


#include "Enemys/AI/Services/NDBTService_TargetLocationToDestination.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UNDBTService_TargetLocationToDestination::UNDBTService_TargetLocationToDestination()
{
	NodeName = "Update the location of the target";
}

void UNDBTService_TargetLocationToDestination::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();

	if (BlackboardComp)
	{
		AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject("Target"));
		FVector TargetLocation = Target->GetActorLocation();
		BlackboardComp->SetValueAsVector("Destination", TargetLocation);
	}
}
