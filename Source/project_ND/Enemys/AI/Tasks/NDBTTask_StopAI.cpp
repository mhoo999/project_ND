﻿// Copyright by project_ND


#include "NDBTTask_StopAI.h"

#include "AIController.h"

UNDBTTask_StopAI::UNDBTTask_StopAI()
{
	NodeName = "Stop AI";
}

EBTNodeResult::Type UNDBTTask_StopAI::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!Pawn)
	{
		return Super::ExecuteTask(OwnerComp, NodeMemory);
	}

	const FVector CurrentLoc = Pawn->GetActorLocation();
	Pawn->SetActorLocation(CurrentLoc);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
