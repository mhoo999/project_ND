// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDWeapon.generated.h"

UCLASS()
class PROJECT_ND_API ANDWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANDWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool Attach(USceneComponent* InParent);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName HolsterSocketName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName EquipSocketName;
};
