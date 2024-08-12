// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDPickUpObject.generated.h"

class ANDPickUpObject;

UENUM(BlueprintType)
enum class EItemType : uint8
{
	HealthPotion	UMETA(DisplayName = "Health Potion"),
	Food			UMETA(DisplayName = "Food"),
	Throwable		UMETA(DisplayName = "Throwable Item"),
	Blunt			UMETA(DisplayName = "Blunt"),
	Revolver		UMETA(DisplayName = "Revolver"),
	Key				UMETA(DisplayName = "Key")
};

USTRUCT(BlueprintType)
struct FItemBaseData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	int32 ItemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FString ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	EItemType Type;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float RecoveryAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float DamageAmount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	UStaticMesh* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TSoftObjectPtr<UTexture2D> ItemThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	bool bNotUse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TSubclassOf<ANDPickUpObject> ItemClass;
};

UCLASS()
class PROJECT_ND_API ANDPickUpObject : public AActor
{
	GENERATED_BODY()

public:
	ANDPickUpObject();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	int32 ItemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	float RecoveryAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	float DamageAmount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	TSoftObjectPtr<UTexture2D> ItemThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	FText Description;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	bool bIsEmpty;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName HolsterSocketName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName EquipSocketName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* DrawMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* SheathMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectSettings")
	UShapeComponent* BodyCollider;

public:
	virtual void OnPickedUp();

	void SetItemMesh(UStaticMesh* Mesh) const;
	
	virtual void InitializeItem(const FItemBaseData& ItemData);

	bool AttachToHolster(USceneComponent* InParent);
	bool AttachToHand   (USceneComponent* InParent);

	UAnimMontage* GetDrawMontage()   { return DrawMontage; }
	UAnimMontage* GetSheathMontage() { return SheathMontage; }

	class ANDMyCharacter* OwnerCharacter;

	UShapeComponent* GetBodyCollider() { return BodyCollider; }
};
