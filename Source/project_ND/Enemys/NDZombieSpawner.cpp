// Copyright by project_ND


#include "NDZombieSpawner.h"

#include "NDZombieBase.h"


ANDZombieSpawner::ANDZombieSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANDZombieSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnZombie();
}

void ANDZombieSpawner::SpawnZombie()
{
	if (bRandSpawn)
	{
		if (const float RandNum = FMath::RandRange(0, 9); RandNum >= 5)
		{
			return;
		}
	}
	
	FVector SpawnLoc = GetActorLocation();
	GetWorld()->SpawnActor<ANDZombieBase>(SpawnTo, SpawnLoc, FRotator::ZeroRotator);

}

