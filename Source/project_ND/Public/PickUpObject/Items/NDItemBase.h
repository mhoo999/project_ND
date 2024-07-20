// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupObject/NDPickupObject.h"
#include "NDItemBase.generated.h"

USTRUCT(BlueprintType)
struct FItemBaseData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(AllowPrivateAccess))
	FString ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(AllowPrivateAccess))
	FString ItemType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(AllowPrivateAccess))
	float RecoveryAmount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(AllowPrivateAccess))
	UStaticMesh* ItemMesh;
	
};

UCLASS()
class PROJECT_ND_API ANDItemBase : public ANDPickupObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANDItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitializeItem(const struct FItemBaseData& ItemData);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectSettings", meta=(AllowPrivateAccess))
	FString ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectSettings", meta=(AllowPrivateAccess))
	float RecoveryAmount;

public:
	void Use();
	
};
