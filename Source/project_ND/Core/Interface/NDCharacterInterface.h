// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NDCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UNDCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_ND_API INDCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void TakeDamage(float DamageAmount)=0;

	virtual void Recovery(FString ItemType, float RecoveryAmount)=0;
	
};
