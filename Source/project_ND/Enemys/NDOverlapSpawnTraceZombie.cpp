// Copyright by project_ND


#include "NDOverlapSpawnTraceZombie.h"

#include "NDTraceZombieSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "project_ND/Core/Characters/NDMyCharacter.h"


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
	if (ANDMyCharacter* Player = Cast<ANDMyCharacter>(OtherActor))
	{
		for (auto Spawner : Spawners)
		{
			Spawner->SpawnZombie(Player);
		}

		FTimerHandle TraceHandle;
		GetWorld()->GetTimerManager().SetTimer(TraceHandle, FTimerDelegate::CreateLambda([&]
		{
			if (AggroSound)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), AggroSound);
			}
		}), 5.f, false);
	}
}

