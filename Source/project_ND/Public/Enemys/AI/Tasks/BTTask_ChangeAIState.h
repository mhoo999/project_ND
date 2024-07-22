// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChangeAIState.generated.h"

enum EAIState : uint8;
class ANDAIController;
/**
 * 
 */
UCLASS()
class PROJECT_ND_API UBTTask_ChangeAIState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ChangeAIState();
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Task", meta=(AllowPrivateAccess))
	FString NewState;
};
