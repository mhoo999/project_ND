// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NDBTTask_CleanBlackBoard.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDBTTask_CleanBlackBoard : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UNDBTTask_CleanBlackBoard();

	UPROPERTY(EditAnywhere, Category="Node")
	TArray<FName> NodeToDelete;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
