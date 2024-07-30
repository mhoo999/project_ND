// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "project_ND/PickUpObject/NDPickUpObject.h"
#include "NDPickUpObject_ItemBase.generated.h"


UCLASS()
class PROJECT_ND_API ANDPickUpObject_ItemBase : public ANDPickUpObject
{
	GENERATED_BODY()

public:
	ANDPickUpObject_ItemBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void Use();
	
};
