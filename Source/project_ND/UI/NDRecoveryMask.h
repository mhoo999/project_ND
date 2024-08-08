// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NDRecoveryMask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDRecoveryMask : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ShowRecoveryMask();
};
