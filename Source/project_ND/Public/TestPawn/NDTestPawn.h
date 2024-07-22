// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NDTestPawn.generated.h"

UCLASS()
class PROJECT_ND_API ANDTestPawn : public APawn
{
	GENERATED_BODY()

public:
	ANDTestPawn();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	UStaticMeshComponent* MeshComponent;
};
