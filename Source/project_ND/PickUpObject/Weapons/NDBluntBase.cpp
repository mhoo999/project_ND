// Copyright by project_ND


#include "NDBluntBase.h"


// Sets default values
ANDBluntBase::ANDBluntBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANDBluntBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANDBluntBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

