// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDItemSpawner_BP.generated.h"

class ANDPickUpObject;

UCLASS()
class PROJECT_ND_API ANDItemSpawner_BP : public AActor
{
	GENERATED_BODY()

public:
	ANDItemSpawner_BP();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpawnTo", meta=(AllowPrivateAccess))
	TArray<TSubclassOf<ANDPickUpObject>> SpawnItemTable;

	void SpawnItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	bool bCanSkipSpawn;
};
