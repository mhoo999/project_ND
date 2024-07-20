// Copyright by project_ND


#include "Enemys/NDNormalZombie.h"


ANDNormalZombie::ANDNormalZombie()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANDNormalZombie::BeginPlay()
{
	Super::BeginPlay();
}

void ANDNormalZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDNormalZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

