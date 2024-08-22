// Copyright by project_ND


#include "NDAIController.h"


#include "NDZombieAnim.h"
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
}

void ANDAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsPrintLog)
	{
		PrintState();
	}
}

void ANDAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Zombie = Cast<ANDZombieBase>(GetPawn());
	RunCurrentBehaviorTree();
}

void ANDAIController::StopAllActions()
{
	BrainComponent->StopLogic(TEXT("StopLogic"));	
	Zombie->GetMesh()->Stop();
}

void ANDAIController::SetAIState(FString NewState)
{
	if (CurrentState == EAIState::Dead)
	{
		return;
	}
	
	BrainComponent->StopLogic(TEXT("Stop Tree"));
	// State 추가하면 StringToEAIState(), RunCurrentBehaviorTree() 함수 확인!
	EAIState EnumState = StringToEAIState(NewState);
	
	if (bChasePlayer && NewState == "Patrol")
	{
		return;
	}
	
	CurrentState = EnumState;
	RunCurrentBehaviorTree();
	
	if (CurrentState == EAIState::Idle)
	{
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
	if (StateString == "Eating")	return EAIState::Eating;
	if (StateString == "Stunned")	return EAIState::Stunned;
	
	return EAIState::Idle;
}

void ANDAIController::RunCurrentBehaviorTree()
{
	StopEating();
	
	switch (CurrentState)
	{
	case EAIState::Idle:
		RunBehaviorTree(IdleBehaviorTree);
		Zombie->StopAllSounds();
		Zombie->PlayIdleAudio();
		break;
	case EAIState::Patrol:
		RunBehaviorTree(PatrolBehaviorTree);
		Zombie->StopAllSounds();
		Zombie->PlayExcitementAudio();
		break;
	case EAIState::Chase:
		RunBehaviorTree(ChaseBehaviorTree);
		break;
	case EAIState::Attack:
		RunBehaviorTree(AttackBehaviorTree);
		Zombie->PlayAttackSound();
		break;
	case EAIState::Dead:
		Zombie->StopAllSounds();
		Zombie->PlayDieSound();
		RunBehaviorTree(DeadBehaviorTree);
		break;
	case EAIState::Eating:
		BeginEating();
		Zombie->PlayEatingAudio();
		RunBehaviorTree(EatingBehaviorTree);
		break;
	case EAIState::Stunned:
		StopAllActions();
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
	
	HearingConfig->HearingRange = 1000.0f;
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->ConfigureSense(*HearingConfig);
	AIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
}

void ANDAIController::GetExcitement() const
{
	Zombie->GetCharacterMovement()->MaxWalkSpeed *= 1.5f;
}

void ANDAIController::GetRelax()
{
	Zombie->GetCharacterMovement()->MaxWalkSpeed = Zombie->GetMovementSpeed();
	bIsExcitement = false;
}

void ANDAIController::OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* Actor : UpdatedActors)
	{
		if (Actor == Cast<ANDZombieBase>(Actor))
		{
			return;
		}
		
		if (!bIsExcitement)
		{
			bIsExcitement = true;
			GetExcitement();
		}
		
		FActorPerceptionBlueprintInfo Info;
		AIPerceptionComponent->GetActorsPerception(Actor, Info);
		
		for (const auto& Stimulus : Info.LastSensedStimuli)
		{
			if (bIsEating == false)
			{
				if (Stimulus.Type == UAISense_Sight::GetSenseID<UAISense_Sight>())
				{
					if (Stimulus.WasSuccessfullySensed())
					{
						SetAIState("Chase");
						GetBlackboardComponent()->SetValueAsObject("Target", Actor);
						bChasePlayer = true;
						return;
					}
				}
			}
			
			if (CurrentState == EAIState::Idle || CurrentState == EAIState::Eating)
			{
				if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
				{
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
}

void ANDAIController::ToggleBeChasePlayer()
{
	bChasePlayer = !bChasePlayer;
}

void ANDAIController::ZombieDie_Implementation()
{
	// BP
}

// void ANDAIController::GetDamaged(FVector HitLocation)
// {
// 	if (!Zombie->bSuperArmor)
// 	{
// 		bIsStiff = true;
// 		BrainComponent->StopLogic(TEXT("Stop Tree"));
// 		UNDZombieAnim* ZombieAnim = Cast<UNDZombieAnim>(Zombie->GetMesh()->GetAnimInstance());
// 		ZombieAnim->PlayDamagedAnim();
// 		
// 		if (CurrentState != EAIState::Chase)
// 		{
// 			FVector Direction = HitLocation - Zombie->GetActorLocation();
// 			FRotator Rotation = Direction.Rotation();
// 			
// 			Zombie->GetMesh()->SetRelativeRotation(Rotation);
// 		}
// 		
// 		FTimerHandle StiffHandle;
// 		GetWorld()->GetTimerManager().ClearTimer(StiffHandle);
// 		GetWorld()->GetTimerManager().SetTimer(StiffHandle, FTimerDelegate::CreateLambda([&]
// 		{
// 			RunCurrentBehaviorTree();
// 			bIsStiff = false;
// 			UE_LOG(LogTemp, Warning, TEXT("Runt Behavior Tree"));
// 		}), 5.0f, false);
// 	}
// }

void ANDAIController::SetPrintLog()
{
	bIsPrintLog = true;
}

EAIState ANDAIController::GetCurrentState()
{
	return CurrentState;
}

void ANDAIController::MakeExcitementZombie()
{
	GetExcitement();
}

void ANDAIController::StopEating()
{
	bIsEating = false;
}

void ANDAIController::BeginEating()
{
	bIsEating = true;
}
