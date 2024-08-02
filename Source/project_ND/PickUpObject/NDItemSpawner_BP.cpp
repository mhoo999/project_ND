// Copyright by project_ND


#include "NDItemSpawner_BP.h"

#include "NDPickUpObject.h"


ANDItemSpawner_BP::ANDItemSpawner_BP()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANDItemSpawner_BP::BeginPlay()
{
	Super::BeginPlay();

	SpawnItem();
}

void ANDItemSpawner_BP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDItemSpawner_BP::SpawnItem()
{
	if (bRandSpawn)
	{
		if (const float RandNum = FMath::RandRange(0, 9); RandNum >= 5)
		{
			return;
		}
	}
	
	if (SpawnItemTable.Max() > 0)
	{
		static const FString ContextString(TEXT("ItemSpawner"));

		if (const TSubclassOf<ANDPickUpObject> SelectedClass = SpawnItemTable[FMath::RandRange(0, SpawnItemTable.Num() - 1)])
		{
			const FVector SpawnLocation = GetActorLocation();
			const float RandYaw = FMath::RandRange(0.0f, 360.0f);
			const FRotator SpawnRotation = FRotator(GetActorRotation().Pitch, RandYaw, GetActorRotation().Roll);

			GetWorld()->SpawnActor<ANDPickUpObject>(SelectedClass, SpawnLocation, SpawnRotation);
		}
	}
}

