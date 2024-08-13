// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "project_ND/Core/Interface/NDCharacterInterface.h"
#include "project_ND/PickUpObject/Weapons/NDWeaponBase.h"
#include "project_ND/PickUpObject/NDPickUpObject.h"
#include "NDMyCharacter.generated.h"

//#include "project_ND/Core/Interface/NDCharacterInterface.h"

class UNDEquipComponent;
class UNDEffectComponent;
class ANDWeaponBase;
class ANDWeapon;
class UNDStatComponent;
class ANDPickUpObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDamaged);

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	UNARMED, FLASHLIGHT, BLUNTWEAPON, THORWABLE, FLASHLIGHTON, REVOLVER
};

UENUM(BlueprintType)
enum class EEquipment : uint8
{
	UNARMED, FIRSTSLOT, SECONDSLOT, THIRDSLOT
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
	EWeaponType GetCurPickUpObjectType() { return CurPickUpObjectType; }

	//ANDWeaponBase* GetCurrentWeapon()
	ANDPickUpObject* GetCurrentPickUpObject()
	{
		if (PickUpObjects.Contains(CurPickUpObjectType))
			return PickUpObjects[CurPickUpObjectType];

		return nullptr;
	}

	void ChangeWeapon(EWeaponType InWeaponType);

	UNDStatComponent* GetStatComponent() { return StatComponent; }
	
	UPROPERTY()
	ANDPickUpObject* CurrentEquipmentItem;
	EEquipment CurrentEquipmentSlot;

	UFUNCTION(BlueprintCallable)
	ANDPickUpObject* GetCurrentEquipmentItem();

	UFUNCTION(BlueprintCallable)
	EEquipment GetCurrentEquipmentSlot();


	UPROPERTY()
	ANDPickUpObject* NextEquipmentItem;
	EEquipment NextEquipmentSLot;

	bool bIsSwap;

private:
	void SpawnWeapons();

public:
	//float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	virtual void TakeDamage(float DamageAmount, AActor* Attacker, FHitResult HitResult) override;

	virtual void Recovery(FString ItemType, float RecoveryAmount) override;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPlayerDamaged OnPlayerDamaged;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void ShowDeathScreen();

private:


protected:
	//Weapon
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//TMap<EWeaponType, ANDWeaponBase*> Weapons;
	//
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//TMap<EWeaponType, TSubclassOf<ANDWeaponBase>> WeaponClasses;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EWeaponType, ANDPickUpObject*> PickUpObjects;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EWeaponType, TSubclassOf<ANDPickUpObject>> PickUpObjectClasses;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EWeaponType  CurPickUpObjectType = EWeaponType::UNARMED;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EWeaponType NextPickUpObjectType = EWeaponType::UNARMED;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UNDStatComponent* StatComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UAnimMontage*   HitMontage;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UAnimMontage* DeathMontage;

	bool bIsCrouched = false;

	bool bIsDead;

protected:
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category="Component", meta=(AllowPrivateAccess))
	UNDEffectComponent* EffectComponent;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category="Component", meta=(AllowPrivateAccess))
	UNDEquipComponent* EquipComponent;


};
