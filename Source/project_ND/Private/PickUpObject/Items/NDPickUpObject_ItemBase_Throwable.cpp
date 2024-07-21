// Copyright by project_ND


#include "..\..\..\Public\PickUpObject\Items\NDPickUpObject_ItemBase_Throwable.h"


ANDPickUpObject_ItemBase_Throwable::ANDPickUpObject_ItemBase_Throwable()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANDPickUpObject_ItemBase_Throwable::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANDPickUpObject_ItemBase_Throwable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDPickUpObject_ItemBase_Throwable::InitializeItem(const FItemBaseData& ItemData)
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

void ANDPickUpObject_ItemBase_Throwable::Use()
{
	Super::Use();

	
}

