// Copyright by project_ND


#include "NDPickUpObject.h"


ANDPickUpObject::ANDPickUpObject()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	SetRootComponent(ItemMesh);
}

void ANDPickUpObject::BeginPlay()
{
	Super::BeginPlay();
}

void ANDPickUpObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDPickUpObject::OnPickedUp()
{
	
}

void ANDPickUpObject::SetItemMesh(UStaticMesh* Mesh) const
{
	ItemMesh->SetStaticMesh(Mesh);
}

void ANDPickUpObject::InitializeItem(const FItemBaseData& ItemData)
{
	ItemID = ItemData.ItemID;
	ItemName = ItemData.ItemName;
	ItemType = ItemData.Type;
	RecoveryAmount = ItemData.RecoveryAmount;
	DamageAmount = ItemData.DamageAmount;
	
	if (ItemData.ItemMesh)
	{
		SetItemMesh(ItemData.ItemMesh);
	}

	ItemThumbnail = ItemData.ItemThumbnail;
	Description = ItemData.Description;
	bIsEmpty = ItemData.bNotUse;
}

