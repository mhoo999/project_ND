// Copyright by project_ND


#include "PickUpObject/NDPickUpObject.h"


// Sets default values
ANDPickUpObject::ANDPickUpObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	SetRootComponent(ItemMesh);
}

// Called when the game starts or when spawned
void ANDPickUpObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
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

