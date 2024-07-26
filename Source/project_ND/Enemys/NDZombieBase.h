// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "project_ND/Core/Interface/NDCharacterInterface.h"
#include "NDZombieBase.generated.h"

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
	
public:
	virtual void TakeDamage(float DamageAmount) override;

	virtual void Recovery(FString ItemType, float RecoveryAmount) override;
	
public:
	float GetHP() const;
	
	void SetHP(float NewHP);


	void InitializeZombie();

	float GetAttackRange() const;

	float GetMovementSpeed() const;
	
};
