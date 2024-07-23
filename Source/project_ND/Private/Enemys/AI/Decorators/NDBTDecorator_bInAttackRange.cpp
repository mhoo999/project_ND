// Copyright by project_ND


#include "Enemys/AI/Decorators/NDBTDecorator_bInAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemys/NDZombieBase.h"

UNDBTDecorator_bInAttackRange::UNDBTDecorator_bInAttackRange()
{
	NodeName = "Is Attack Range";
}

bool UNDBTDecorator_bInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	ANDZombieBase* Zombie = Cast<ANDZombieBase>(AIController->GetPawn());
	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();

	float AttackRange = Zombie->GetAttackRange();
	float TargetDistance = BlackboardComponent->GetValueAsFloat("TargetDistance");
	
	if (AttackRange >= TargetDistance)
	{
		return true;
	}

	return false;
	// return Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
}
