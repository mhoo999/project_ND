// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupObject/NDPickUpObject.h"
#include "NDPickUpObject_ItemBase.generated.h"

UENUM()
enum EMyEnum
{
	HealthPotion,
	Food,
	Throwable
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(AllowPrivateAccess))
	bool bIsEmpty;	
	
};

UCLASS()
class PROJECT_ND_API ANDPickUpObject_ItemBase : public ANDPickUpObject
{
	GENERATED_BODY()

public:
	ANDPickUpObject_ItemBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(AllowPrivateAccess))
	FString ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(AllowPrivateAccess))
	float RecoveryAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(AllowPrivateAccess))
	bool bIsEmpty;
	
public:
	virtual void InitializeItem(const struct FItemBaseData& ItemData);
	
	virtual void Use();
	
};
