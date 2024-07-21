// Copyright by project_ND


#include "PickUpObject/Items/NDPickUpObject_ItemBase_HealthPotion.h"


ANDPickUpObject_ItemBase_HealthPotion::ANDPickUpObject_ItemBase_HealthPotion()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANDPickUpObject_ItemBase_HealthPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANDPickUpObject_ItemBase_HealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDPickUpObject_ItemBase_HealthPotion::InitializeItem(const FItemBaseData& ItemData)
{
	Super::InitializeItem(ItemData);

	SetItemName(ItemData.ItemName);
	ItemType = ItemData.ItemType;
	RecoveryAmount = ItemData.RecoveryAmount;
	bIsEmpty = ItemData.bIsEmpty;
	
	if (ItemData.ItemMesh)
	{
		SetItemMesh(ItemData.ItemMesh);
	}
}

void ANDPickUpObject_ItemBase_HealthPotion::Use()
{
	Super::Use();

	
}

