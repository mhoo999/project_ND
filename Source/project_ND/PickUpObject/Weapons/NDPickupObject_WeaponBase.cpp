// Copyright by project_ND


#include "NDPickupObject_WeaponBase.h"


// Sets default values
ANDPickupObject_WeaponBase::ANDPickupObject_WeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANDPickupObject_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANDPickupObject_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDPickupObject_WeaponBase::Attack()
{
	
}

