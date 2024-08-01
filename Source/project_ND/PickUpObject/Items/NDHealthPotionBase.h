// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "NDItemBase.h"
#include "NDHealthPotionBase.generated.h"

UCLASS()
class PROJECT_ND_API ANDHealthPotionBase : public ANDItemBase
{
	GENERATED_BODY()

public:
	ANDHealthPotionBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Use() override;
};
