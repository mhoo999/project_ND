// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "NDItemBase.h"
#include "NDThrowableBase.generated.h"

class UAIPerceptionStimuliSourceComponent;
class UProjectileMovementComponent;

UCLASS()
class PROJECT_ND_API ANDThrowableBase : public ANDItemBase
{
	GENERATED_BODY()

public:
	ANDThrowableBase();

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
