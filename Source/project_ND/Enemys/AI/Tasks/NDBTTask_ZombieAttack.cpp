// Copyright by project_ND


#include "NDBTTask_ZombieAttack.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "project_ND/Core/Enemys/NDZombieAnim.h"

UNDBTTask_ZombieAttack::UNDBTTask_ZombieAttack()
{
	NodeName = "Zombie attack";
}

// EBTNodeResult::Type UNDBTTask_ZombieAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
// {
// 	AAIController* const MuController = OwnerComp.GetAIOwner();
// 	EBTNodeResult::Type Result = EBTNodeResult::Failed;
// 	
// 	TimerHandle.Invalidate();
// 	MyOwnerComp = &OwnerComp;
// 	
// 	if (AnimationToPlay)
// 	{
// 		if (UNDZombieAnim* AnimInstance = Cast<UNDZombieAnim>(Character->GetMesh()->GetAnimInstance()))
// 		{
// 			AnimInstance->PlayZombieAttack();
// 		}
// 	}
// }
