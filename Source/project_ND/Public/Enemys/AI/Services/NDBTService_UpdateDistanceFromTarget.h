// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "NDBTService_UpdateDistanceFromTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDBTService_UpdateDistanceFromTarget : public UBTService
{
	GENERATED_BODY()

public:
	UNDBTService_UpdateDistanceFromTarget();

private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
