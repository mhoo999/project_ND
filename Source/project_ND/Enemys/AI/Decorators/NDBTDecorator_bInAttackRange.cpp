// Copyright by project_ND


#include "NDBTDecorator_bInAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "project_ND/Enemys/NDZombieBase.h"

UNDBTDecorator_bInAttackRange::UNDBTDecorator_bInAttackRange()
{
	NodeName = "Is Attack Range";
}

bool UNDBTDecorator_bInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return false;
	}
	
	const ANDZombieBase* Zombie = Cast<ANDZombieBase>(AIController->GetPawn());
	if (!Zombie)
	{
		return false;
	}
	
	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
	if (!BlackboardComponent)
	{
		return false;
	}

	const FName TargetDistanceKey = "TargetDistance";
	const float AttackRange = Zombie->GetAttackRange();
	const float TargetDistance = BlackboardComponent->GetValueAsFloat(TargetDistanceKey);
	
	return AttackRange >= TargetDistance;
}
