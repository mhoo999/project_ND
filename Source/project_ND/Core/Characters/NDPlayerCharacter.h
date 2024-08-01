// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NDMyCharacter.h"
#include "NDPlayerCharacter.generated.h"

struct FInputActionValue;


UCLASS()
class PROJECT_ND_API APlayerCharacter : public ANDMyCharacter
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

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Walk(const FInputActionValue& Value);
	void OnJump();

	void CrouchStart(const FInputActionValue& Value);
	void CrouchEnd  (const FInputActionValue& Value);

	void SprintStart();
	void SprintEnd  ();

	void OnFlashLightKey(const FInputActionValue& Value);
	void OnBluntWeaponKey(const FInputActionValue& Value);

	void StrafeOn();
	void StrafeOff();

	UFUNCTION(BlueprintCallable)
	void OnDrawEnd();

	UFUNCTION(BlueprintCallable)
	void OnSheathEnd();

	void OnAttack();

	UFUNCTION(BlueprintCallable)
	void OnAttackBegin();
	
	UFUNCTION(BlueprintCallable)
	void OnAttackEnd();
	//void Crouched(const FInputActionValue& Value);

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class UNDInputComponent* MyInputComponent;
};
