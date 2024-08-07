// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "project_ND/PickUpObject/NDPickUpObject.h"
#include "NDWeaponBase.generated.h"

UCLASS()
class PROJECT_ND_API ANDWeaponBase : public ANDPickUpObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANDWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectSettings")
	FString WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectSettings")
	float WeaponDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectSettings")
	float WeaponRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectSettings")
	int32 AmmoCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectSettings")
	UShapeComponent* BodyCollider;
	
public:
	bool AttachToHolster(USceneComponent* InParent);
	bool AttachToHand   (USceneComponent* InParent);


	UAnimMontage* GetDrawMontage()   { return DrawMontage; }
	UAnimMontage* GetSheathMontage() { return SheathMontage; }

	void Attack();

	UShapeComponent* GetBodyCollider() { return BodyCollider; }


protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName HolsterSocketName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName EquipSocketName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* DrawMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* SheathMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* AttackMontage;

	class ANDMyCharacter* OwnerCharacter;
	
	class ANDZombieBase* Target;

};
