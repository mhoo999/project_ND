// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NDHitMask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDHitMask : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void ShowHitMask();
};
