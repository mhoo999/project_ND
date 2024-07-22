// Copyright by project_ND


#include "Enemys/AI/Tasks/BTTask_PlayRandomAnimation.h"

#include "Core/Enemys/NDAIController.h"
#include "Enemys/NDZombieBase.h"

UBTTask_PlayRandomAnimation::UBTTask_PlayRandomAnimation()
{
	NodeName = "Play Random Animation";
}

EBTNodeResult::Type UBTTask_PlayRandomAnimation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
