// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NDPickupObject.generated.h"

UCLASS()
class PROJECT_ND_API ANDPickupObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANDPickupObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectSettings", meta=(AllowPrivateAccess))
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectSettings", meta=(AllowPrivateAccess))
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectSettings", meta=(AllowPrivateAccess))
	UStaticMeshComponent* ItemMesh;

public:
	virtual void OnPickedUp();

	void SetItemName(FString Name);

	void SetItemMesh(UStaticMesh* Mesh) const;
};
