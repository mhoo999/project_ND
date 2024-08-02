// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NDUpgradeSelector.generated.h"

class ANDPlayerController;
/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDUpgradeSelector : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UDataTable* UpgradeOptionTable;

	void ChooseUpgrade();
};
