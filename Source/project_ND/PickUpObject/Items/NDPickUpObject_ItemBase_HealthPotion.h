// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "NDPickUpObject_ItemBase.h"
#include "NDPickUpObject_ItemBase_HealthPotion.generated.h"

UCLASS()
class PROJECT_ND_API ANDPickUpObject_ItemBase_HealthPotion : public ANDPickUpObject_ItemBase
{
	GENERATED_BODY()

public:
	ANDPickUpObject_ItemBase_HealthPotion();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void InitializeItem(const FItemBaseData& ItemData) override;

	virtual void Use() override;
};
