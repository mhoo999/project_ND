// Copyright by project_ND


#include "TestPawn/NDTestGameMode.h"

#include "TestPawn/NDTestController.h"
#include "TestPawn/NDTestPawn.h"

ANDTestGameMode::ANDTestGameMode()
{
	DefaultPawnClass = ANDTestPawn::StaticClass();
	PlayerControllerClass = ANDTestController::StaticClass();
}
