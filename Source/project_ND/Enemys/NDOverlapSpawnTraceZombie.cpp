// Copyright by project_ND


#include "NDOverlapSpawnTraceZombie.h"

#include "NDTraceZombieSpawner.h"
#include "Components/BoxComponent.h"


ANDOverlapSpawnTraceZombie::ANDOverlapSpawnTraceZombie()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Box"));
	SetRootComponent(BoxComponent);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ANDOverlapSpawnTraceZombie::OnBoxBeginOverlap);
}

void ANDOverlapSpawnTraceZombie::BeginPlay()
{
	Super::BeginPlay();

	
}

void ANDOverlapSpawnTraceZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDOverlapSpawnTraceZombie::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* Player = Cast<APawn>(OtherActor))
	{
		for (auto Spawner : Spawners)
		{
			Spawner->SpawnZombie(Player);
		}
	}
}

