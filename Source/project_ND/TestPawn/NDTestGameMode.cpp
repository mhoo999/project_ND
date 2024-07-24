// Copyright by project_ND


#include "NDTestGameMode.h"

#include "NDTestController.h"
#include "NDTestPawn.h"

ANDTestGameMode::ANDTestGameMode()
{
	DefaultPawnClass = ANDTestPawn::StaticClass();
	PlayerControllerClass = ANDTestController::StaticClass();
}
