// Copyright by project_ND


#include "Core/Enemys/NDAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "UObject/ConstructorHelpers.h"


ANDAIController::ANDAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	// To initialize a BehaviorTree
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
	
	// To initialize a AI Perception
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	SetPerceptionComponent(*AIPerceptionComponent);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->SightRadius = 1000.0f;
	SightConfig->LoseSightRadius = 1200.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	HearingConfig->HearingRange = 3000.0f;
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->ConfigureSense(*HearingConfig);
	AIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());

	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ANDAIController::OnPerceptionUpdate);
}

void ANDAIController::BeginPlay()
{
	Super::BeginPlay();

	RunCurrentBehaviorTree();
}

void ANDAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	PrintState();
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

void ANDAIController::PrintState()
{
	FString StateString = UEnum::GetValueAsString(CurrentState);
	FString CleanStateString = StateString.Mid(StateString.Find(TEXT("."), ESearchCase::IgnoreCase, ESearchDir::FromEnd) + 1);

	DrawDebugString(GetWorld(), GetPawn()->GetActorLocation(), CleanStateString, nullptr, FColor::Yellow, 0, true, 1);
}

void ANDAIController::OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* Actor : UpdatedActors)
	{
		FActorPerceptionBlueprintInfo Info;
		AIPerceptionComponent->GetActorsPerception(Actor, Info);

		for (const auto& Stimulus : Info.LastSensedStimuli)
		{
			if (Stimulus.Type == UAISense_Sight::GetSenseID<UAISense_Sight>())
			{
				if (Stimulus.WasSuccessfullySensed())
				{
					SetAIState(EAIState::Chase);
					// BB의 타겟을 Actor로 바꿔 Chase하도록 만들어야 함
					return;
				}
			}
			else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
			{
				if (Stimulus.WasSuccessfullySensed())
				{
					SetAIState(EAIState::Patrol);
					// BB의 타겟을 Stimulus.StimulusLocation으로
					return;
				}
			}
		}
	}
}
