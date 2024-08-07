// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDItemSpawner_DT.generated.h"

class ANDRevolverBase;
class ANDBluntBase;
class ANDThrowableBase;
class ANDFoodBase;
class ANDHealthPotionBase;

UCLASS()
class PROJECT_ND_API ANDItemSpawner_DT : public AActor
{
	GENERATED_BODY()

public:
	ANDItemSpawner_DT();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning", meta=(AllowPrivateAccess))
	UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning", meta=(AllowPrivateAccess))
	TSubclassOf<ANDHealthPotionBase> ItemClass_HealthPotion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning", meta=(AllowPrivateAccess))
	TSubclassOf<ANDFoodBase> ItemClass_Food;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning", meta=(AllowPrivateAccess))
	TSubclassOf<ANDThrowableBase> ItemClass_Throwable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning", meta=(AllowPrivateAccess))
	TSubclassOf<ANDBluntBase> ItemClass_Blunt;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning", meta=(AllowPrivateAccess))
	TSubclassOf<ANDRevolverBase> ItemClass_Revolver;
	
public:
	UFUNCTION(BlueprintCallable, Category="Spawning")
	void SpawnItem();
	
};
