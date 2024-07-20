// Copyright by project_ND


#include "PickUpObject/NDPickupObject.h"


// Sets default values
ANDPickupObject::ANDPickupObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	SetRootComponent(ItemMesh);
}

// Called when the game starts or when spawned
void ANDPickupObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANDPickupObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDPickupObject::OnPickedUp()
{
	
}

void ANDPickupObject::SetItemName(FString Name)
{
	ItemName = Name;
}

void ANDPickupObject::SetItemMesh(UStaticMesh* Mesh) const
{
	ItemMesh->SetStaticMesh(Mesh);
}

