// Copyright by project_ND


#include "NDBTService_UpdateDistanceFromTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UNDBTService_UpdateDistanceFromTarget::UNDBTService_UpdateDistanceFromTarget()
{
	NodeName = "Update distance from target";
}

void UNDBTService_UpdateDistanceFromTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                     float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return;
	}

	const APawn* Pawn = AIController->GetPawn();
	if (!Pawn)
	{
		return;
	}
	
	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
	if (!BlackboardComponent)
	{
		return;
	}
	
	const FName TargetKey = "Target";
	const AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetKey));
	if (!Target)
	{
		return;
	}

	const float TargetDistance = FVector::Dist(Pawn->GetActorLocation(), Target->GetActorLocation());
	
	const FName TargetDistanceKey = "TargetDistance";
	BlackboardComponent->SetValueAsFloat(TargetDistanceKey, TargetDistance);
}
