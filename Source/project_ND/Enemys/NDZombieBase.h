﻿// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "project_ND/Core/Interface/NDCharacterInterface.h"
#include "NDZombieBase.generated.h"

UENUM(BlueprintType)
enum class EHitLocation : uint8
{
	Head		UMETA(DisplayName = "Head"),
	Chest		UMETA(DisplayName = "Chest"),
	Pelvis		UMETA(DisplayName = "Pelvis"),
	LeftArm		UMETA(DisplayName = "Left Arm"),
	RightArm	UMETA(DisplayName = "Right Arm"),
	LeftLeg		UMETA(DisplayName = "Left Leg"),
	RightLeg	UMETA(DisplayName = "Right Leg")
};

UCLASS()
class PROJECT_ND_API ANDZombieBase : public ACharacter, public INDCharacterInterface
{
	GENERATED_BODY()

public:
	ANDZombieBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
protected:
	float HP;
	float Damage;
	float Range;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Status", meta=(AllowPrivateAccess))
	float InitialHP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Status", meta=(AllowPrivateAccess))
	float MovementSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Status", meta=(AllowPrivateAccess))
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Status", meta=(AllowPrivateAccess))
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HitLocation", meta=(AllowPrivateAccess))
	EHitLocation HitLocation;

	bool bSuperArmor;

	void SetHitLocationByBoneName(const FName& BoneName);
	
public:
	virtual void TakeDamage(float DamageAmount) override;

	virtual void Recovery(FString ItemType, float RecoveryAmount) override;
	
	float GetHP() const;
	
	void SetHP(float NewHP);
	
	void InitializeZombie();

	float GetAttackRange() const;

	float GetMovementSpeed() const;
	
};
