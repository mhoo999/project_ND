// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "NDZombieBase.h"
#include "NDNormalZombie.generated.h"

UCLASS()
class PROJECT_ND_API ANDNormalZombie : public ANDZombieBase
{
	GENERATED_BODY()

public:
	ANDNormalZombie();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
