// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "NDBTService_TargetLocationToDestination.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDBTService_TargetLocationToDestination : public UBTService
{
	GENERATED_BODY()

public:
	UNDBTService_TargetLocationToDestination();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
