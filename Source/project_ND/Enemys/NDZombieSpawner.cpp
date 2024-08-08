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
	FRotator SpawnRot = GetActorRotation();
	
	if (ANDZombieBase* SpawnZombie = GetWorld()->SpawnActor<ANDZombieBase>(SpawnTo, SpawnLoc, SpawnRot))
	{
		if (ANDAIController* AIController = Cast<ANDAIController>(SpawnZombie->GetController()))
		{
			if (bStartEating)
			{
				AIController->SetAIState("Eating");
			}

			if (bPrintLog)
			{
				AIController->SetPrintLog();
			}
		}
	}
}

