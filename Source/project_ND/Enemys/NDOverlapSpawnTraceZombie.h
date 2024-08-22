// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDOverlapSpawnTraceZombie.generated.h"

class UBoxComponent;
class ANDTraceZombieSpawner;

UCLASS()
class PROJECT_ND_API ANDOverlapSpawnTraceZombie : public AActor
{
	GENERATED_BODY()

public:
	ANDOverlapSpawnTraceZombie();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property", meta=(AllowPrivateAccess))
	UBoxComponent* BoxComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	TArray<ANDTraceZombieSpawner*> Spawners;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="settings", meta=(AllowPrivateAccess))
	USoundBase* AggroSound;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
