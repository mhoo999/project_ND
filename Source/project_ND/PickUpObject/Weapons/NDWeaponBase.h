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

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectSettings")
	//UShapeComponent* BodyCollider;
	
public:

	//UShapeComponent* GetBodyCollider() { return BodyCollider; }

	void Attack();

	virtual void OnAttackBegin();
	virtual void OnAttackEnd();

protected:

	class ANDZombieBase* Target;

	class ANDMyCharacter* OwnerCharacter;
};
