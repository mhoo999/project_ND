// Copyright by project_ND


#include "Enemys/AI/Tasks/NDBTTask_StopAI.h"

#include "AIController.h"
#include "AIHelpers.h"

UNDBTTask_StopAI::UNDBTTask_StopAI()
{
	NodeName = "Stop AI";
}

EBTNodeResult::Type UNDBTTask_StopAI::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController->GetPawn();

	FVector CurrentLoc = Pawn->GetActorLocation();
	Pawn->SetActorLocation(CurrentLoc);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
