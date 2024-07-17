// Copyright Epic Games, Inc. All Rights Reserved.

#include "project_NDGameMode.h"
#include "project_NDCharacter.h"
#include "UObject/ConstructorHelpers.h"

Aproject_NDGameMode::Aproject_NDGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
