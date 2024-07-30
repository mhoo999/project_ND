// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "NDPickUpObject_ItemBase.h"
#include "NDPickUpObject_ItemBase_Throwable.generated.h"

class UAIPerceptionStimuliSourceComponent;
class UProjectileMovementComponent;

UCLASS()
class PROJECT_ND_API ANDPickUpObject_ItemBase_Throwable : public ANDPickUpObject_ItemBase
{
	GENERATED_BODY()

public:
	ANDPickUpObject_ItemBase_Throwable();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	USoundBase* BreakSound;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	UProjectileMovementComponent* ProjectileMovementComponent;

	virtual void Tick(float DeltaTime) override;

	virtual void Use() override;

	bool bCanNoise = true;
	FTimerHandle NoiseTimerHandle;
	
};
