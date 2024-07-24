// Copyright by project_ND


#include "Enemys/AI/Services/NDBTService_UpdateDistanceFromTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Chaos/Utilities.h"

UNDBTService_UpdateDistanceFromTarget::UNDBTService_UpdateDistanceFromTarget()
{
	NodeName = "Update distance from target";
}

void UNDBTService_UpdateDistanceFromTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                     float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController->GetPawn();
	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
	AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject("Target"));
	
	float TargetDistance = FVector::Dist(Pawn->GetActorLocation(), Target->GetActorLocation());
	
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsFloat("TargetDistance", TargetDistance);
	}
}
