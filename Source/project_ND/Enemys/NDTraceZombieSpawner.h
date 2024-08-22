// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDTraceZombieSpawner.generated.h"

class ANDAIController;
class AAIController;
class ANDZombieBase;

UCLASS()
class PROJECT_ND_API ANDTraceZombieSpawner : public AActor
{
	GENERATED_BODY()

public:
	ANDTraceZombieSpawner();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	TSubclassOf<ANDZombieBase> SpawnTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	float TraceTime = 5.0f;
	
	bool bIsRunning;

	UPROPERTY()
	ANDAIController* ZombieController;

	UPROPERTY()
	APawn* Target;
	
public:
	void SpawnZombie(APawn* Player);
};
