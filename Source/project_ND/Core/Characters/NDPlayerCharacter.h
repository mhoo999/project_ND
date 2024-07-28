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

	bool GetIsCrouched() { return bIsCrouched; }

	UFUNCTION(BlueprintCallable)
	EWeaponType GetCurWeaponType() { return CurWeaponType; }

	ANDWeapon* GetCurrentWeapon()
	{
		if (Weapons.Contains(CurWeaponType))
			return Weapons[CurWeaponType];

		return nullptr;
	}

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Walk(const FInputActionValue& Value);

	void CrouchStart(const FInputActionValue& Value);
	void CrouchEnd  (const FInputActionValue& Value);

	void SprintStart();
	void SprintEnd  ();

	void OnFlashLightKey(const FInputActionValue& Value);

	void ChangeWeapon(EWeaponType InWeaponType);

	void StrafeOn();
	void StrafeOff();

	UFUNCTION(BlueprintCallable)
	void OnDrawEnd();

	UFUNCTION(BlueprintCallable)
	void OnSheathEnd();

	//void Crouched(const FInputActionValue& Value);

protected:
	bool bIsWalking   = false;
	bool bIsSprinting = false;
	bool bIsCrouched  = false;

	//Weapon
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EWeaponType, ANDWeapon*> Weapons;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EWeaponType, TSubclassOf<ANDWeapon>> WeaponClasses;

	EWeaponType  CurWeaponType = EWeaponType::UNARMED;
	EWeaponType NextWeaponType = EWeaponType::UNARMED;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UNDInputComponent* MyInputComponent;
};
