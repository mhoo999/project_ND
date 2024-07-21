// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "NDPickUpObject_ItemBase.h"
#include "NDPickUpObject_ItemBase_Throwable.generated.h"

UCLASS()
class PROJECT_ND_API ANDPickUpObject_ItemBase_Throwable : public ANDPickUpObject_ItemBase
{
	GENERATED_BODY()

public:
	ANDPickUpObject_ItemBase_Throwable();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void InitializeItem(const struct FItemBaseData& ItemData);

	virtual void Use() override;

};
