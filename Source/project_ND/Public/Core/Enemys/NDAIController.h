// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "NDAIController.generated.h"

UENUM()
enum EAIState : uint8
{
	Idle,
	Patrol,
	Chase,
	Attack,
	Dead
};

UCLASS()
class PROJECT_ND_API ANDAIController : public AAIController
{
	GENERATED_BODY()

public:
	ANDAIController();

protected:
	virtual void BeginPlay() override;

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
	
};
