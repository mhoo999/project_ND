﻿// Copyright by project_ND


#include "NDBTTask_PlayRandomAnimation.h"

#include "project_ND/Core/Enemys/NDAIController.h"
#include "project_ND/Enemys/NDZombieBase.h"

UNDBTTask_PlayRandomAnimation::UNDBTTask_PlayRandomAnimation()
{
	NodeName = "Play Random Animation";
}

EBTNodeResult::Type UNDBTTask_PlayRandomAnimation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANDAIController* AIController = Cast<ANDAIController>(OwnerComp.GetAIOwner());
	ANDZombieBase* Zombie = AIController->GetPawn<ANDZombieBase>();

	int8 LandNum = FMath::RandRange(0, Montages.Num() - 1);
	UAnimSequence* SelectedSequence = Montages[LandNum];

	if (SelectedSequence)
	{
		Zombie->GetMesh()->PlayAnimation(SelectedSequence, false);
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}