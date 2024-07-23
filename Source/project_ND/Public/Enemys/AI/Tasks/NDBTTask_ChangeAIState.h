// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NDBTTask_ChangeAIState.generated.h"

enum EAIState : uint8;
class ANDAIController;
/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDBTTask_ChangeAIState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UNDBTTask_ChangeAIState();
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Task", meta=(AllowPrivateAccess))
	FString NewState;
};
