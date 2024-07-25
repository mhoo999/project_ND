// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NDPlayerCharacter.generated.h"

struct FInputActionValue;
class ANDWeapon;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	UNARMED, FLASHLIGHT
};

UCLASS()
class PROJECT_ND_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Walk(const FInputActionValue& Value);

	void CrouchStart(const FInputActionValue& Value);
	void CrouchEnd  (const FInputActionValue& Value);

	void SprintStart();
	void SprintEnd  ();

	//void Crouched(const FInputActionValue& Value);

public:

	bool GetIsCrouched() { return bIsCrouched; }

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputMappingContext* MappingContext;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* MoveAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* JumpAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* LookAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* WalkAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* SprintAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* CrouchAction;

	bool bIsWalking   = false;
	bool bIsSprinting = false;
	bool bIsCrouched  = false;

	//Weapon

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EWeaponType, ANDWeapon*> Weapons;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EWeaponType, TSubclassOf<ANDWeapon>> WeaponClasses;


};