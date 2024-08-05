// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "NDAIController.generated.h"

class ANDZombieBase;
class UAISenseConfig_Hearing;
class UAISenseConfig_Sight;

UENUM()
enum EAIState : uint8
{
	Idle	UMETA(DisplayName = "Idle State"),
	Patrol	UMETA(DisplayName = "Patrol State"),
	Chase	UMETA(DisplayName = "Chase State"),
	Attack	UMETA(DisplayName = "Attack State"),
	Dead	UMETA(DisplayName = "Dead State")
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

public:
	void SetAIState(FString NewState);

	static EAIState StringToEAIState(const FString& StateString);
	
private:
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

	EAIState CurrentState;
	
	void RunCurrentBehaviorTree();

	void PrintState();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess))
	ANDZombieBase* Zombie;
	
	void InitializeBehaviorTree();
	void InitializeAIPerception() const;

	bool bIsExcitement;
	FTimerHandle RelaxTimerHandle;
	void GetExcitement() const;
	void GetRelax();

	bool bChasePlayer;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	UAISenseConfig_Hearing* HearingConfig;

	UFUNCTION()
	void OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors);
	
public:
	void ToggleBeChasePlayer();

	UFUNCTION(BlueprintNativeEvent)
	void ZombieDie();
	virtual void ZombieDie_Implementation();
};
