// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NDMyCharacter.generated.h"

class ANDWeapon;
class UNDStatComponent;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	UNARMED, FLASHLIGHT, BLUNTWEAPON
};

UCLASS()
class PROJECT_ND_API ANDMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANDMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	EWeaponType GetCurWeaponType() { return CurWeaponType; }

	ANDWeapon* GetCurrentWeapon()
	{
		if (Weapons.Contains(CurWeaponType))
			return Weapons[CurWeaponType];

		return nullptr;
	}

	void ChangeWeapon(EWeaponType InWeaponType);
	
	UNDStatComponent* GetStatComponent() { return StatComponent; }


private:
	void SpawnWeapons();

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

protected:
	//Weapon
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EWeaponType, ANDWeapon*> Weapons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EWeaponType, TSubclassOf<ANDWeapon>> WeaponClasses;

	EWeaponType  CurWeaponType = EWeaponType::UNARMED;
	EWeaponType NextWeaponType = EWeaponType::UNARMED;


	bool bIsCrouched = false;

	UNDStatComponent* StatComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UAnimMontage*   HitMontage;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UAnimMontage* DeathMontage;
};
