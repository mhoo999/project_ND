// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "NDPickUpObject_ItemBase.h"
#include "NDPickUpObject_ItemBase_Food.generated.h"

UCLASS()
class PROJECT_ND_API ANDPickUpObject_ItemBase_Food : public ANDPickUpObject_ItemBase
{
	GENERATED_BODY()

public:
	ANDPickUpObject_ItemBase_Food();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Use() override;

};
