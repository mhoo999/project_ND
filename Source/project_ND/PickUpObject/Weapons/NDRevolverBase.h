// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "NDWeaponBase.h"
#include "NDRevolverBase.generated.h"

UCLASS()
class PROJECT_ND_API ANDRevolverBase : public ANDWeaponBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANDRevolverBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnAttackBegin();
	virtual void OnAttackEnd();

public:
	void Reload();
	void OnReloadMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void FinishReloading();
	bool IsReloading() const;

	uint32 GetCurBullets();
	uint32 GetMaxBullets();

protected:
	uint32 CurBullets;
	uint32 MaxBullets;
	bool bIsReloading;
	float relodingDelayTime = 3.0f;
	float BulletLifespan = 2.0f;

	FTimerHandle ReloadTimerHandle;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<class ANDBulletBase> BulletClassReference;

	TArray<class ANDBulletBase*> Bullets;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UAnimMontage* ReloadMontage;

};
