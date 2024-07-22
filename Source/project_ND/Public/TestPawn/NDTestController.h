// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "NDTestController.generated.h"

UCLASS()
class PROJECT_ND_API ANDTestController : public APlayerController
{
	GENERATED_BODY()

public:
	ANDTestController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent() override;
};
