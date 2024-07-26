// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDItemSpawner.generated.h"

class ANDPickUpObject_ItemBase_Throwable;
class ANDPickUpObject_ItemBase_Food;
class ANDPickUpObject_ItemBase;
class ANDPickUpObject_ItemBase_HealthPotion;

UCLASS()
class PROJECT_ND_API ANDItemSpawner : public AActor
{
	GENERATED_BODY()

public:
	ANDItemSpawner();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning", meta=(AllowPrivateAccess))
	UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning", meta=(AllowPrivateAccess))
	TSubclassOf<ANDPickUpObject_ItemBase_HealthPotion> ItemClass_HealthPotion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning", meta=(AllowPrivateAccess))
	TSubclassOf<ANDPickUpObject_ItemBase_Food> ItemClass_Food;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning", meta=(AllowPrivateAccess))
	TSubclassOf<ANDPickUpObject_ItemBase_Throwable> ItemClass_Throwable;

public:
	UFUNCTION(BlueprintCallable, Category="Spawning")
	void SpawnItem();
	
};
