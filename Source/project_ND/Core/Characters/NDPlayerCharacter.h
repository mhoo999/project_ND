// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NDMyCharacter.h"
#include "NDPlayerCharacter.generated.h"


struct FInputActionValue;


UCLASS()
class PROJECT_ND_API ANDPlayerCharacter : public ANDMyCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANDPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool GetIsCrouched() { return bIsCrouched; }

	virtual void TakeDamage(float DamageAmount, AActor* Attacker, FHitResult HitResult) override;


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

	UFUNCTION(BlueprintCallable)
	void FootStepSound();

	void OnAttack();

	UFUNCTION(BlueprintImplementableEvent)
	void Throwables();


	UFUNCTION(BlueprintCallable)
	void OnAttackBegin();
	
	UFUNCTION(BlueprintCallable)
	void OnAttackEnd();

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void HandlePlayerDamaged();

	void ChangeToMainCamera();
	void ChangeToAimCamera();

	UFUNCTION(BlueprintCallable)
	void FlashLightOn();

	UFUNCTION(BlueprintCallable)
	void ToggleFlashLightVisibility();

	UFUNCTION(BlueprintCallable)
	void RevolverReload();

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class UNDInputComponent* MyInputComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UTimelineComponent* ZoomTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UTimelineComponent* CrouchTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCurveFloat* ZoomCurve;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Camera")
	class UCameraComponent* PCamera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Camera")
	class UCameraComponent* AimCamera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TSubclassOf<UCameraShakeBase> MyCameraShakeClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SportLight")
	class USpringArmComponent* FlahsSpringArm;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SportLight")
	class USpotLightComponent* FlashLightSpot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USceneComponent* ProjectilStart;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USplineComponent* ProjectilPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* StepSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* FlashSound;

	class ANDZombieBase* Target;

	//class ANDWeaponBase* weapon;

	FVector DefaultCameraLocation;
	FVector ZoomOutLocation;

	FVector DefaulCrouchLocation;
	FVector CrouchedLocation;

	bool bIsCharging = false;
	bool bHasWeaponEquip;
	bool bIsFlashLightOn;

public:
	UFUNCTION(BlueprintCallable)
	void ChangeState();

private:
	bool bIsAttackTrace;

	void PerformHandSphereTraces();

	UPROPERTY()
	ANDPickUpObject* TraceWeapon;
	
public:
	void StartBluntAttack(ANDPickUpObject* Item);
	void EndBluntAttack();
};
