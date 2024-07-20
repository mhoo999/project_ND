// Copyright by project_ND


#include "PickUpObject/Items/NDItemBase.h"


// Sets default values
ANDItemBase::ANDItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANDItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANDItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDItemBase::InitializeItem(const FItemBaseData& ItemData)
{
	SetItemName(ItemData.ItemName);
	ItemType = ItemData.ItemType;
	RecoveryAmount = ItemData.RecoveryAmount;
	if (ItemData.ItemMesh)
	{
		SetItemMesh(ItemData.ItemMesh);
	}
}

void ANDItemBase::Use()
{
	
}

