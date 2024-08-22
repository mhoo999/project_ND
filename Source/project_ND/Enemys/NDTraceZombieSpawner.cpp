// Copyright by project_ND


#include "NDTraceZombieSpawner.h"

#include "NDZombieBase.h"
#include "project_ND/Core/Enemys/NDAIController.h"


ANDTraceZombieSpawner::ANDTraceZombieSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANDTraceZombieSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANDTraceZombieSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDTraceZombieSpawner::SpawnZombie(APawn* Player)
{
	if (bIsRunning == false)
	{
		bIsRunning = true;
		FVector SpawnLoc = GetActorLocation();
		FRotator SpawnRot = GetActorRotation();
		
		if (ANDZombieBase* SpawnZombie = GetWorld()->SpawnActor<ANDZombieBase>(SpawnTo, SpawnLoc, SpawnRot))
		{
			ZombieController = Cast<ANDAIController>(SpawnZombie->GetController());
			Target = Player;
			
			FTimerHandle TraceHandle;
			GetWorld()->GetTimerManager().SetTimer(TraceHandle, FTimerDelegate::CreateLambda([&]
			{
				if (ZombieController)
				{
					ZombieController->MakeExcitementZombie();
					ZombieController->MoveToActor(Target);
				}
			}), TraceTime, false);
		}
	}
}

