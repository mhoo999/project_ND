// Copyright by project_ND


#include "NDBTTask_PlayRandomAnimation.h"

#include "project_ND/Core/Enemys/NDAIController.h"
#include "project_ND/Enemys/NDZombieBase.h"

UNDBTTask_PlayRandomAnimation::UNDBTTask_PlayRandomAnimation()
{
	NodeName = "Play Random Animation";
}

EBTNodeResult::Type UNDBTTask_PlayRandomAnimation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const ANDZombieBase* Zombie = Cast<ANDAIController>(OwnerComp.GetAIOwner())->GetPawn<ANDZombieBase>();
	if (!Zombie)
	{
		return Super::ExecuteTask(OwnerComp, NodeMemory);
	}

	const int8 LandNum = FMath::RandRange(0, Montages.Num() - 1);

	if (UAnimSequence* SelectedSequence = Montages[LandNum])
	{
		Zombie->GetMesh()->PlayAnimation(SelectedSequence, false);
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
