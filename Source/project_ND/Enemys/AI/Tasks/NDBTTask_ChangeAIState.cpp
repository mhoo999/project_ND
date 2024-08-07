// Copyright by project_ND


#include "NDBTTask_ChangeAIState.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "project_ND/Core/Enemys/NDAIController.h"

UNDBTTask_ChangeAIState::UNDBTTask_ChangeAIState()
{
	NodeName = "Change ai state";
}

EBTNodeResult::Type UNDBTTask_ChangeAIState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANDAIController* AIController = Cast<ANDAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return Super::ExecuteTask(OwnerComp, NodeMemory);
	}

	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
	if (!BlackboardComponent)
	{
		return Super::ExecuteTask(OwnerComp, NodeMemory);
	}

	const FName TargetDistanceKey = "TargetDistance";
	constexpr float DistanceKey = 10000.0f;
	BlackboardComponent->SetValueAsFloat(TargetDistanceKey, DistanceKey);
	AIController->SetAIState(NewState);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
