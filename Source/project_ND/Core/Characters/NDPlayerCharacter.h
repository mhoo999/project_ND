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

	UFUNCTION()
	void HandleCrouchProgress(float Value);

	UFUNCTION()
	void HandleZoomProgress(float Value);

	void SprintStart();
	void SprintEnd  ();

	void FlashLightOn();

	void OnFlashLightKey(const FInputActionValue& Value);
	void ChangeFirstSlotItem(const FInputActionValue& Value);
	void ChangeSecondSlotItem(const FInputActionValue& Value);
	void ChangeThirdSlotItem(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintImplementableEvent)
	void BPThrowable();

	void StrafeOn();
	void StrafeOff();

	UFUNCTION(BlueprintCallable)
	void OnDrawEnd();

	UFUNCTION(BlueprintCallable)
	void OnSheathEnd();

	void OnAttack();


	UFUNCTION(BlueprintImplementableEvent)
	void Throwables();
	void OnAttackPressed();
	
	void OnAttackReleased();


	UFUNCTION(BlueprintCallable)
	void OnAttackBegin();
	
	UFUNCTION(BlueprintCallable)
	void OnAttackEnd();
	//void Crouched(const FInputActionValue& Value);

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class UNDInputComponent* MyInputComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UTimelineComponent* ZoomTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UTimelineComponent* CrouchTimeline;

	// ÁÜ È¿°ú¸¦ À§ÇÑ °î¼±
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCurveFloat* ZoomCurve;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PCamera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USceneComponent* ProjectilStart;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USplineComponent* ProjectilPath;


	//ANDZombieBase* Target;
	class ANDZombieBase* Target;

	//class ANDWeaponBase* weapon;

	FVector DefaultCameraLocation;
	FVector ZoomOutLocation;

	FVector DefaulCrouchLocation;
	FVector CrouchedLocation;
};
