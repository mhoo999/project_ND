// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "NDAIController.generated.h"

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

public:
	void SetAIState(EAIState NewState);
	
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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	UAISenseConfig_Hearing* HearingConfig;

	UFUNCTION()
	void OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors);
};
