// Copyright by project_ND


#include "..\..\..\Public\PickUpObject\Items\NDPickUpObject_ItemBase_Food.h"


ANDPickUpObject_ItemBase_Food::ANDPickUpObject_ItemBase_Food()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANDPickUpObject_ItemBase_Food::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANDPickUpObject_ItemBase_Food::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDPickUpObject_ItemBase_Food::InitializeItem(const FItemBaseData& ItemData)
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

void ANDPickUpObject_ItemBase_Food::Use()
{
	Super::Use();

	
}

