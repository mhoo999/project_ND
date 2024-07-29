// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NDTestPawn.generated.h"

class UCapsuleComponent;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	UCapsuleComponent* ClubCapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	UStaticMeshComponent* ClubMeshComponent;

	void SetClubLeft(float Value);
	void SetClubRight(float Value);
	bool bClubLeft;
	void Attack(float Value);
	bool bAttacking;
	
	UFUNCTION()
	void OnCollisionComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
