// Copyright by project_ND


#include "Core/Enemys/NDAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UObject/ConstructorHelpers.h"


ANDAIController::ANDAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> IdleBTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/Project_ND/Core/Enemys/BT_Idle.BT_Idle'"));
	if (IdleBTObject.Succeeded())
	{
		IdleBehaviorTree = IdleBTObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> PatrolBTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/Project_ND/Core/Enemys/BT_Patrol.BT_Patrol'"));
	if (PatrolBTObject.Succeeded())
	{
		PatrolBehaviorTree = PatrolBTObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> ChaseBTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/Project_ND/Core/Enemys/BT_Chase.BT_Chase'"));
	if (ChaseBTObject.Succeeded())
	{
		ChaseBehaviorTree = ChaseBTObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AttackBTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/Project_ND/Core/Enemys/BT_Attack.BT_Attack'"));
	if (AttackBTObject.Succeeded())
	{
		AttackBehaviorTree = AttackBTObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> DeadBTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/Project_ND/Core/Enemys/BT_Dead.BT_Dead'"));
	if (DeadBTObject.Succeeded())
	{
		DeadBehaviorTree = DeadBTObject.Object;
	}

	CurrentState = EAIState::Idle;
}

void ANDAIController::BeginPlay()
{
	Super::BeginPlay();

	RunCurrentBehaviorTree();
}

void ANDAIController::SetAIState(EAIState NewState)
{
	if (CurrentState != NewState)
	{
		CurrentState = NewState;
		RunCurrentBehaviorTree();
	}
}

void ANDAIController::RunCurrentBehaviorTree()
{
	switch (CurrentState)
	{
	case EAIState::Idle:
		RunBehaviorTree(IdleBehaviorTree);
		break;
	case EAIState::Patrol:
		RunBehaviorTree(ChaseBehaviorTree);
		break;
	case EAIState::Chase:
		RunBehaviorTree(ChaseBehaviorTree);
		break;
	case EAIState::Attack:
		RunBehaviorTree(AttackBehaviorTree);
		break;
	case EAIState::Dead:
		RunBehaviorTree(DeadBehaviorTree);
		break;
	default:
		break;
	}
}
