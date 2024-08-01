// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "project_ND/PickUpObject/NDPickUpObject.h"
#include "NDItemBase.generated.h"


UCLASS()
class PROJECT_ND_API ANDItemBase : public ANDPickUpObject
{
	GENERATED_BODY()

public:
	ANDItemBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void Use();
	
};
