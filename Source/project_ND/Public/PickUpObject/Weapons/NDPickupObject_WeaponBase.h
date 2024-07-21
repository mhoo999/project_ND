// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupObject/NDPickUpObject.h"
#include "NDPickupObject_WeaponBase.generated.h"

UCLASS()
class PROJECT_ND_API ANDPickupObject_WeaponBase : public ANDPickUpObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANDPickupObject_WeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectSettings", meta=(AllowPrivateAccess))
	FString WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectSettings", meta=(AllowPrivateAccess))
	float WeaponDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectSettings", meta=(AllowPrivateAccess))
	float WeaponRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectSettings", meta=(AllowPrivateAccess))
	int32 AmmoCount;

public:
	void Attack();
	
};
