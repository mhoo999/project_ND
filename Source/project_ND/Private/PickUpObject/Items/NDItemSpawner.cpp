// Copyright by project_ND


#include "PickUpObject/Items/NDItemSpawner.h"

#include "..\..\..\Public\PickUpObject\Items\NDPickUpObject_ItemBase.h"
#include "PickUpObject/Items/NDPickUpObject_ItemBase_Food.h"
#include "PickUpObject/Items/NDPickUpObject_ItemBase_HealthPotion.h"
#include "PickUpObject/Items/NDPickUpObject_ItemBase_Throwable.h"


ANDItemSpawner::ANDItemSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UDataTable> DTObject(TEXT("/Script/Engine.DataTable'/Game/Project_ND/PickUpObject/Items/DT_Items.DT_Items'"));
	if (DTObject.Succeeded())
	{
		ItemDataTable = DTObject.Object;
	}
	
}

void ANDItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnItem();
}

void ANDItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDItemSpawner::SpawnItem()
{
	if (ItemDataTable)
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

				TSubclassOf<ANDPickUpObject_ItemBase> SelectedClass;

				if (SelectedItem->ItemType == "HealthPotion")
				{
					SelectedClass = ItemClass_HealthPotion;
				}
				else if (SelectedItem->ItemType == "Food")
				{
					SelectedClass = ItemClass_Food;
				}
				else if (SelectedItem->ItemType == "Throwable")
				{
					SelectedClass = ItemClass_Throwable;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Unknown item type : %s"), *SelectedItem->ItemType);
					return;
				}

				// UE_LOG(LogTemp, Warning, TEXT("Selected type : %s"), *SelectedItem->ItemType);

				if (SelectedClass)
				{
					FVector SpawnLocation = GetActorLocation();
					float RandYaw = FMath::RandRange(0.0f, 360.0f);
					FRotator SpawnRotation = FRotator(GetActorRotation().Pitch, RandYaw, GetActorRotation().Roll);
					ANDPickUpObject_ItemBase* SpawnedItem = GetWorld()->SpawnActor<ANDPickUpObject_ItemBase>(SelectedClass, SpawnLocation, SpawnRotation);

					if (SpawnedItem)
					{
						SpawnedItem->InitializeItem(*SelectedItem);
					}
				}
			}
		}
	}
}

