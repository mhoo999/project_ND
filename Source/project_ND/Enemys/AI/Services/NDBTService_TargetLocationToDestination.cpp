// Copyright by project_ND


#include "NDBTService_TargetLocationToDestination.h"

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

	if (UBlackboardComponent* BlackboardComp = OwnerComp.GetAIOwner()->GetBlackboardComponent())
	{
		const AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject("Target"));
		const FVector TargetLocation = Target->GetActorLocation();
		BlackboardComp->SetValueAsVector("Destination", TargetLocation);
	}
}
