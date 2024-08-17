// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDBulletBase.generated.h"

UCLASS()
class PROJECT_ND_API ANDBulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANDBulletBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetActive(bool IsActive);

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class UShapeComponent* Collider;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class UParticleSystemComponent* TrailEffect;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class UProjectileMovementComponent* ProjectileMovement;

	bool bIsActive = false;
};
