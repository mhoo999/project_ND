// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "NDAIController.generated.h"

class ANDZombieBase;
class UAISenseConfig_Hearing;
class UAISenseConfig_Sight;

UENUM(BlueprintType)
enum EAIState : uint8
{
	Idle	UMETA(DisplayName = "Idle State"),
	Patrol	UMETA(DisplayName = "Patrol State"),
	Chase	UMETA(DisplayName = "Chase State"),
	Attack	UMETA(DisplayName = "Attack State"),
	Dead	UMETA(DisplayName = "Dead State"),
	Eating	UMETA(DisplayName = "Eating State"),
	Stunned UMETA(DisplayName = "Stunned State")
};

UCLASS()
class PROJECT_ND_API ANDAIController : public AAIController
{
	GENERATED_BODY()

public:
	ANDAIController();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	ANDZombieBase* Zombie;
	
	UPROPERTY(EditDefaultsOnly, Category="AI", meta=(AllowPrivateAccess))
	UBehaviorTree* IdleBehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category="AI", meta=(AllowPrivateAccess))
	UBehaviorTree* PatrolBehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category="AI", meta=(AllowPrivateAccess))
	UBehaviorTree* ChaseBehaviorTree;
	
	UPROPERTY(EditDefaultsOnly, Category="AI", meta=(AllowPrivateAccess))
	UBehaviorTree* AttackBehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category="AI", meta=(AllowPrivateAccess))
	UBehaviorTree* DeadBehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category="AI", meta=(AllowPrivateAccess))
	UBehaviorTree* EatingBehaviorTree;

	EAIState CurrentState;
	
	static EAIState StringToEAIState(const FString& StateString);
	
	void PrintState();

	bool bChasePlayer;
	bool bIsExcitement;
	FTimerHandle RelaxTimerHandle;
	void GetExcitement() const;
	void GetRelax();
	
	void InitializeBehaviorTree();
	
	void InitializeAIPerception() const;
	
	UPROPERTY(BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess))
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess))
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess))
	UAISenseConfig_Hearing* HearingConfig;

	UFUNCTION()
	void OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors);
	
	bool bIsPrintLog;
	
	void StopEating();
	void BeginEating();
	bool bIsEating;

	void StopAllActions();
	bool bIsStunned;

public:
	void SetAIState(FString NewState);

	void RunCurrentBehaviorTree();
	
	void ToggleBeChasePlayer();

	UFUNCTION(BlueprintNativeEvent)
	void ZombieDie();
	virtual void ZombieDie_Implementation();

	// void GetDamaged(FVector HitLocation);

	void SetPrintLog();

	EAIState GetCurrentState();

	void MakeExcitementZombie();

private:
	bool bIsStun;
};
