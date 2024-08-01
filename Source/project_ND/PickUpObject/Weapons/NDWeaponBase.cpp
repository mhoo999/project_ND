// Copyright by project_ND


#include "NDWeaponBase.h"


// Sets default values
ANDWeaponBase::ANDWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANDWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANDWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDWeaponBase::Attack()
{
	
}

