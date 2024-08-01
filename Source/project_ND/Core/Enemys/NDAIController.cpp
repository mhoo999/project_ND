// Copyright by project_ND


#include "NDAIController.h"


#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "project_ND/Enemys/NDZombieBase.h"
#include "UObject/ConstructorHelpers.h"


ANDAIController::ANDAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	InitializeBehaviorTree();
	
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	SetPerceptionComponent(*AIPerceptionComponent);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	InitializeAIPerception();
	
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

	if (Zombie)
	{
		if (Zombie->GetHP() == 0.0f)
		{
			SetAIState("Dead");
		}
	}
}

void ANDAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Zombie = Cast<ANDZombieBase>(GetPawn());
}

void ANDAIController::SetAIState(FString NewState)
{
	if (CurrentState == EAIState::Dead)
	{
		return;
	}
	
	BrainComponent->StopLogic(TEXT("Stop Tree"));
	EAIState EnumState = StringToEAIState(NewState);
	
	if (bChasePlayer && NewState == "Patrol")
	{
		return;
	}
	
	CurrentState = EnumState;
	RunCurrentBehaviorTree();
	
	if (CurrentState == EAIState::Idle)
	{
		bIsExcitement = false;
		GetWorld()->GetTimerManager().ClearTimer(RelaxTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(RelaxTimerHandle, FTimerDelegate::CreateLambda([&]
		{
			GetRelax();
		}), 5.0f, false);
	}
}

EAIState ANDAIController::StringToEAIState(const FString& StateString)
{
	if (StateString == "Patrol")	return EAIState::Patrol;
	if (StateString == "Chase")		return EAIState::Chase;
	if (StateString == "Attack")	return EAIState::Attack;
	if (StateString == "Dead")		return EAIState::Dead;
	
	return EAIState::Idle;
}

void ANDAIController::RunCurrentBehaviorTree()
{
	switch (CurrentState)
	{
	case EAIState::Idle:
		RunBehaviorTree(IdleBehaviorTree);
		break;
	case EAIState::Patrol:
		RunBehaviorTree(PatrolBehaviorTree);
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
	// Zombie Info
	FString StateString = UEnum::GetValueAsString(CurrentState);
	FString isExcitement = bIsExcitement ? "Excitement" : "Relax";
	FString CleanStateString = StateString.Mid(StateString.Find(TEXT("."), ESearchCase::IgnoreCase, ESearchDir::FromEnd) + 1) + "(" + isExcitement + ")";
	float ZombieHP = Zombie->GetHP();
	
	// BlackBoard Values
	AActor* TargetActor = Cast<AActor>(GetBlackboardComponent()->GetValueAsObject("Target"));
	float TargetDistance = GetBlackboardComponent()->GetValueAsFloat("TargetDistance");
	FVector Destination = GetBlackboardComponent()->GetValueAsVector("Destination");

	FString TargetActorInfo = TargetActor ? TargetActor->GetName() + TEXT(" @ ") + FString::SanitizeFloat(FMath::TruncToInt(TargetDistance)) : TEXT("None");
	FString DestinationString = FString::Printf(TEXT("X: %lld, Y: %lld, Z: %lld"), FMath::TruncToInt(Destination.X), FMath::TruncToInt(Destination.Y), FMath::TruncToInt(Destination.Z));

	FString DebugString = "HP: " + FString::SanitizeFloat(ZombieHP) + "\n" + "state: " + CleanStateString + "\n" + "Target: " + TargetActorInfo + "\n" + "Dest: " + DestinationString;
	
	DrawDebugString(GetWorld(), GetPawn()->GetActorLocation(), DebugString, nullptr, FColor::Yellow, 0, true, 1);
}

void ANDAIController::InitializeBehaviorTree()
{
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

void ANDAIController::InitializeAIPerception() const
{
	SightConfig->SightRadius = 700.0f;
	SightConfig->LoseSightRadius = 900.0f;
	SightConfig->PeripheralVisionAngleDegrees = 45.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 500.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	
	HearingConfig->HearingRange = 1500.0f;
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->ConfigureSense(*HearingConfig);
	AIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
}

void ANDAIController::GetExcitement() const
{
	Zombie->GetCharacterMovement()->MaxWalkSpeed *= 3.0f;
}

void ANDAIController::GetRelax() const
{
	Zombie->GetCharacterMovement()->MaxWalkSpeed = Zombie->GetMovementSpeed();
}

void ANDAIController::OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* Actor : UpdatedActors)
	{
		if (!bIsExcitement)
		{
			bIsExcitement = true;
			GetExcitement();
		}
		
		FActorPerceptionBlueprintInfo Info;
		AIPerceptionComponent->GetActorsPerception(Actor, Info);
		
		for (const auto& Stimulus : Info.LastSensedStimuli)
		{
			if (Stimulus.Type == UAISense_Sight::GetSenseID<UAISense_Sight>())
			{
				UE_LOG(LogTemp, Warning, TEXT("Detected Object Name : %s, Type : Sight"), *Actor->GetName());
				
				if (Stimulus.WasSuccessfullySensed())
				{
					SetAIState("Chase");
					GetBlackboardComponent()->SetValueAsObject("Target", Actor);
					bChasePlayer = true;
					return;
				}
			}
			else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
			{
				UE_LOG(LogTemp, Warning, TEXT("Detected Object Name : %s, Type : Hearing"), *Actor->GetName());

				if (Stimulus.WasSuccessfullySensed() && CurrentState != EAIState::Chase)
				{
					SetAIState("Patrol");
					GetBlackboardComponent()->SetValueAsObject("Target", Actor);
					GetBlackboardComponent()->SetValueAsVector("Destination", Actor->GetActorLocation());
					return;
				}
			}
		}
	}
}

void ANDAIController::ToggleBeChasePlayer()
{
	bChasePlayer = !bChasePlayer;
}

void ANDAIController::ZombieDie()
{
	if (AIPerceptionComponent)
	{
		GetAIPerceptionComponent()->Deactivate();
	}

	if (BrainComponent)
	{
		BrainComponent->StopLogic(TEXT("Stop Tree"));
	}

	if (Zombie)
	{
		Zombie->GetMesh()->SetSimulatePhysics(true);
		Zombie->GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	}
}
