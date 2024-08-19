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

protected:
	int32 CurBullets;
	int32 MaxBullets;
	bool bIsReloading;

	void Reload();
	void OnReloadMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void FinishReloading();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<class ANDBulletBase> BulletClassReference;

	TArray<class ANDBulletBase*> Bullets;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UAnimMontage* ReloadMontage;

};
