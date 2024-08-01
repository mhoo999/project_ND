// Copyright by project_ND


#include "NDItemSpawner.h"

#include "Items/NDFoodBase.h"
#include "Items/NDHealthPotionBase.h"
#include "Items/NDThrowableBase.h"
#include "project_ND/PickUpObject/Items/NDItemBase.h"
#include "Weapons/NDBluntBase.h"
#include "Weapons/NDRevolverBase.h"


ANDItemSpawner::ANDItemSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

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
				if (SelectedItem->bNotUse)
				{
					return;
				}

				TSubclassOf<ANDItemBase> SelectedClass;

				if (SelectedItem->Type == EItemType::HealthPotion)
				{
					SelectedClass = ItemClass_HealthPotion;
				}
				else if (SelectedItem->Type == EItemType::Food)
				{
					SelectedClass = ItemClass_Food;
				}
				else if (SelectedItem->Type == EItemType::Throwable)
				{
					SelectedClass = ItemClass_Throwable;
				}
				else if (SelectedItem->Type == EItemType::Blunt)
				{
					SelectedClass = ItemClass_Blunt;

				}
				else if (SelectedItem->Type == EItemType::Revolver)
				{
					SelectedClass = ItemClass_Revolver;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Unknown item type : %hhd"), SelectedItem->Type);
					return;
				}

				// UE_LOG(LogTemp, Warning, TEXT("Selected type : %s"), *SelectedItem->ItemType);

				if (SelectedClass)
				{
					FVector SpawnLocation = GetActorLocation();
					float RandYaw = FMath::RandRange(0.0f, 360.0f);
					FRotator SpawnRotation = FRotator(GetActorRotation().Pitch, RandYaw, GetActorRotation().Roll);
					ANDItemBase* SpawnedItem = GetWorld()->SpawnActor<ANDItemBase>(SelectedClass, SpawnLocation, SpawnRotation);

					if (SpawnedItem)
					{
						SpawnedItem->InitializeItem(*SelectedItem);
					}
				}
			}
		}
	}
}

