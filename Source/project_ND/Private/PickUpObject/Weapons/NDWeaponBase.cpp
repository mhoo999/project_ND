// Copyright by project_ND


#include "..\..\..\Public\PickUpObject\Weapons\NDWeaponBase.h"


// Sets default values
ANDWeapons::ANDWeapons()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANDWeapons::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANDWeapons::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDWeapons::Attack()
{
	
}

