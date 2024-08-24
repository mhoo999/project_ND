// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDPickUpObject.generated.h"

class USphereComponent;
class ANDPickUpObject;

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None			UMETA(DisplayName = "None"),
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
	int32 ItemID = -1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FString ItemName = TEXT("Unknown Item");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	EItemType Type = EItemType::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float RecoveryAmount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float DamageAmount = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	UStaticMesh* ItemMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TSoftObjectPtr<UTexture2D> ItemThumbnail = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FText Description = FText::FromString(TEXT("No Description"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	bool bNotUse = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TSubclassOf<ANDPickUpObject> ItemClass = nullptr;

	FItemBaseData()
		: ItemID(-1)
		, ItemName(TEXT("Unknown Item"))
		, Type(EItemType::None)
		, RecoveryAmount(0.0f)
		, DamageAmount(0.0f)
		, ItemMesh(nullptr)
		, ItemThumbnail(nullptr)
		, Description(FText::FromString(TEXT("No Description")))
		, bNotUse(false)
		, ItemClass(nullptr)
	{
	}
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UShapeComponent* BodyCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Component")
	USphereComponent* SphereComponent;

public:
	virtual void OnAttackBegin();
	virtual void OnAttackEnd();

	virtual void OnPickedUp();

	void SetItemMesh(UStaticMesh* Mesh) const;
	
	virtual void InitializeItem(const FItemBaseData& ItemData);

	bool AttachToHolster(USceneComponent* InParent);
	bool AttachToHand   (USceneComponent* InParent);

	UAnimMontage* GetDrawMontage()   { return DrawMontage; }
	UAnimMontage* GetSheathMontage() { return SheathMontage; }

	class ANDMyCharacter* OwnerCharacter;

	UShapeComponent* GetBodyCollider() { return BodyCollider; }

	void SetSimulate();

	float GetDamageAmount();

private:
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	bool bIsEquip;

public:
	void bIsEquipTrue();

};
