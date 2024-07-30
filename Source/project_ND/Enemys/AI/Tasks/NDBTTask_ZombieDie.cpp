// Copyright by project_ND


#include "NDBTTask_ZombieDie.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "project_ND/Core/Enemys/NDAIController.h"

UNDBTTask_ZombieDie::UNDBTTask_ZombieDie()
{
	NodeName = "Zombie die";
}

EBTNodeResult::Type UNDBTTask_ZombieDie::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANDAIController* AIController = Cast<ANDAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return Super::ExecuteTask(OwnerComp, NodeMemory);
	}

	AIController->ZombieDie();
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
