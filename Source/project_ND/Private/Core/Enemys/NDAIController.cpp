// Copyright by project_ND


#include "Core/Enemys/NDAIController.h"


// Sets default values
ANDAIController::ANDAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANDAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANDAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

