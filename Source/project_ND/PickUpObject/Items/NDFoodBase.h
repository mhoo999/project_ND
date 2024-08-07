// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "NDItemBase.h"
#include "NDFoodBase.generated.h"

UCLASS()
class PROJECT_ND_API ANDFoodBase : public ANDItemBase
{
	GENERATED_BODY()

public:
	ANDFoodBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Use() override;

};
