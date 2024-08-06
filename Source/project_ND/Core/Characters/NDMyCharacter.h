// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "project_ND/Core/Interface/NDCharacterInterface.h"
#include "project_ND/PickUpObject/Weapons/NDWeaponBase.h"
#include "NDMyCharacter.generated.h"
//#include "project_ND/Core/Interface/NDCharacterInterface.h"

class ANDWeaponBase;
class ANDWeapon;
class UNDStatComponent;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	UNARMED, FLASHLIGHT, BLUNTWEAPON, THORWABLE
};

UCLASS()
class PROJECT_ND_API ANDMyCharacter : public ACharacter, public INDCharacterInterface
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

	ANDWeaponBase* GetCurrentWeapon()
	{
		if (Weapons.Contains(CurWeaponType))
			return Weapons[CurWeaponType];

		return nullptr;
	}

	void ChangeWeapon(EWeaponType InWeaponType);
	
	UNDStatComponent* GetStatComponent() { return StatComponent; }


private:
	void SpawnWeapons();

public:
	//float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	virtual void TakeDamage(float DamageAmount, AActor* Attacker, FHitResult HitResult) override;

	virtual void Recovery(FString ItemType, float RecoveryAmount) override;

protected:
	//Weapon
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EWeaponType, ANDWeaponBase*> Weapons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EWeaponType, TSubclassOf<ANDWeaponBase>> WeaponClasses;

	EWeaponType  CurWeaponType = EWeaponType::UNARMED;
	EWeaponType NextWeaponType = EWeaponType::UNARMED;


	bool bIsCrouched = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UNDStatComponent* StatComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UAnimMontage*   HitMontage;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UAnimMontage* DeathMontage;
};
