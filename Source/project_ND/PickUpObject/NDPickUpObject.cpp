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

void ANDPickUpObject::SetItemName(FString Name)
{
	ItemName = Name;
}

void ANDPickUpObject::SetItemMesh(UStaticMesh* Mesh) const
{
	ItemMesh->SetStaticMesh(Mesh);
}

void ANDPickUpObject::InitializeItem(const FItemBaseData& ItemData)
{
	SetItemName(ItemData.ItemName);
	ItemType = ItemData.Type;
	RecoveryAmount = ItemData.RecoveryAmount;
	bIsEmpty = ItemData.bNotUse;
	
	if (ItemData.ItemMesh)
	{
		SetItemMesh(ItemData.ItemMesh);
	}
}

