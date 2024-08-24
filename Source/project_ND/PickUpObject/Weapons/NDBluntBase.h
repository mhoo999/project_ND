// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "NDWeaponBase.h"
#include "NDBluntBase.generated.h"

UCLASS()
class PROJECT_ND_API ANDBluntBase : public ANDWeaponBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANDBluntBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void BluntSwingSound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	USoundBase* SwingSound;

	bool bIsAttackTrace;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnAttackBegin();
	virtual void OnAttackEnd();

	void InitializeBlunt();
};
