// Copyright by project_ND


#include "TestPawn/NDTestController.h"


ANDTestController::ANDTestController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANDTestController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANDTestController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward");
	InputComponent->BindAxis("MoveRight");
}
