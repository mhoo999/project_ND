// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NDZombieBase.generated.h"

UCLASS()
class PROJECT_ND_API ANDZombieBase : public ACharacter
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
	float GetHP() const;
	
	void SetHP(float NewHP);

	void TakeDamage(float DamageAmount);

	void InitializeZombie();

	float GetAttackRange() const;
	
};
