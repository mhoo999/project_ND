// Copyright by project_ND


#include "NDZombieSpawner.h"

#include "NDZombieBase.h"
#include "project_ND/Core/Enemys/NDAIController.h"


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
	ANDZombieBase* SpawnZombie = GetWorld()->SpawnActor<ANDZombieBase>(SpawnTo, SpawnLoc, FRotator::ZeroRotator);

	if (bStartEating && SpawnZombie)
	{
		if (ANDAIController* AIController = Cast<ANDAIController>(SpawnZombie->GetController()))
		{
			AIController->SetAIState("Eating");
		}
	}
}

