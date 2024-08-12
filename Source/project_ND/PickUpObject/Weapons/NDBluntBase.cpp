// Copyright by project_ND


#include "NDBluntBase.h"

#include "Kismet/GameplayStatics.h"
#include "project_ND/Core/Characters/NDMyCharacter.h"
#include "Components/ShapeComponent.h"
#include "project_ND/Enemys/NDZombieBase.h"
#include "project_ND/Core/Components/NDStatComponent.h"

ANDBluntBase::ANDBluntBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANDBluntBase::BeginPlay()
{
	Super::BeginPlay();
	
	BodyCollider->OnComponentBeginOverlap.AddDynamic(this, &ANDBluntBase::OnBodyColliderBeginOverlap);
}

void ANDBluntBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDBluntBase::OnBodyColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == OwnerCharacter)
	{
		return;
	}
	
	if(ANDZombieBase* Zombie = Cast<ANDZombieBase>(OtherActor))
	{
		Zombie->TakeDamage(10.0f, OwnerCharacter, SweepResult);
	}
}

