// Copyright by project_ND


#include "NDBTTask_DieAnimBefore.h"

#include "AIController.h"
#include "project_ND/Enemys/NDZombieBase.h"

UNDBTTask_DieAnimBefore::UNDBTTask_DieAnimBefore()
{
	NodeName = "Die before";
}

EBTNodeResult::Type UNDBTTask_DieAnimBefore::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ANDZombieBase* Zombie = Cast<ANDZombieBase>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		Zombie->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
