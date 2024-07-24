// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NDTestPawn.generated.h"

class UArrowComponent;
class ANDPickUpObject_ItemBase_Throwable;
class UCameraComponent;

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
	void MoveUp(float Value);
	void SpawnThrowable(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	TSubclassOf<ANDPickUpObject_ItemBase_Throwable> TestItem;

	bool bCanSpawn = true;
	FTimerHandle SpawnTimerHandle;
};
