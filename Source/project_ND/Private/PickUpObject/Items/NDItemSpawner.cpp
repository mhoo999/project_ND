// Copyright by project_ND


#include "PickUpObject/Items/NDItemSpawner.h"

#include "PickUpObject/Items/NDItemBase.h"


// Sets default values
ANDItemSpawner::ANDItemSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANDItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnItem();
}

// Called every frame
void ANDItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDItemSpawner::SpawnItem()
{
	if (ItemDataTable && ItemClass)
	{
		static const FString ContextString(TEXT("ItemSpawner"));
		TArray<FItemBaseData*> Items;
		ItemDataTable->GetAllRows<FItemBaseData>(ContextString, Items);

		if (Items.Num() > 0)
		{
			FItemBaseData* SelectedItem = Items[FMath::RandRange(0, Items.Num() - 1)];

			if (SelectedItem)
			{
				if (SelectedItem->bIsEmpty)
				{
					return;
				}
				
				FVector SpawnLocation = GetActorLocation();
				FRotator SpawnRotation = GetActorRotation();
				ANDItemBase* SpawnedItem = GetWorld()->SpawnActor<ANDItemBase>(ItemClass, SpawnLocation, SpawnRotation);

				if (SpawnedItem)
				{
					SpawnedItem->InitializeItem(*SelectedItem);
				}
			}
		}
	}
}

