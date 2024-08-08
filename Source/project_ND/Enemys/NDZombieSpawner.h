// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDZombieSpawner.generated.h"

class ANDZombieBase;

UCLASS()
class PROJECT_ND_API ANDZombieSpawner : public AActor
{
	GENERATED_BODY()

public:
	ANDZombieSpawner();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	TSubclassOf<ANDZombieBase> SpawnTo;

	void SpawnZombie();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	bool bRandSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	bool bStartEating;
};
