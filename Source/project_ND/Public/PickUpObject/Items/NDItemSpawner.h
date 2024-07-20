// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDItemSpawner.generated.h"

UCLASS()
class PROJECT_ND_API ANDItemSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANDItemSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning", meta=(AllowPrivateAccess))
	UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning", meta=(AllowPrivateAccess))
	TSubclassOf<class ANDItemBase> ItemClass;

public:
	UFUNCTION(BlueprintCallable, Category="Spawning")
	void SpawnItem();
	
};
