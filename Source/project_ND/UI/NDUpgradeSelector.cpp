// Copyright by project_ND


#include "NDUpgradeSelector.h"

#include "Components/Image.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "project_ND/Core/Characters/NDMyCharacter.h"
#include "project_ND/Core/Components/NDStatComponent.h"

void UNDUpgradeSelector::OptionSorting()
{
    if (UpgradeOptionTable)
    {
        static const FString ContextString(TEXT("OptionSorting"));
        TArray<FUpgradeOptionTable*> OptionRows;
        UpgradeOptionTable->GetAllRows<FUpgradeOptionTable>(ContextString, OptionRows);

        TSet<int32> SelectedIndices;
        while (SelectedIndices.Num() < 3 && SelectedIndices.Num() < OptionRows.Num())
        {
            int32 RandomIndex = FMath::RandRange(0, OptionRows.Num() - 1);
            SelectedIndices.Add(RandomIndex);
        }

        TArray<FUpgradeOptionTable*> Options = { &Option01, &Option02, &Option03 };
        TArray<UImage*> OptionImages = { Option01Image, Option02Image, Option03Image };
        int32 Index = 0;

        for (auto SelectedIndex : SelectedIndices)
        {
            if (OptionRows.IsValidIndex(SelectedIndex) && OptionImages.IsValidIndex(Index))
            {
                if (OptionRows[SelectedIndex]->Image)
                {
                    OptionImages[Index]->SetBrushFromTexture(OptionRows[SelectedIndex]->Image);
                }
                
                *Options[Index] = *OptionRows[SelectedIndex];
            
                Index++;
            }
        }
    }
}

void UNDUpgradeSelector::ChooseUpgrade(FUpgradeOptionTable Option)
{
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        if (ANDMyCharacter* Player = Cast<ANDMyCharacter>(PlayerController->GetPawn()))
        {
            if (UNDStatComponent* StatComponent = Player->GetComponentByClass<UNDStatComponent>())
            {
                StatComponent->UpgradeStat(Option);
            }
        }
    }
}

void UNDUpgradeSelector::OnOption01ButtonHovered()
{
}

void UNDUpgradeSelector::OnOption01UnButtonHovered()
{
}

void UNDUpgradeSelector::OnOption02ButtonHovered()
{
}

void UNDUpgradeSelector::OnOption02UnButtonHovered()
{
}

void UNDUpgradeSelector::OnOption03ButtonHovered()
{
}

void UNDUpgradeSelector::OnOption03UnButtonHovered()
{
}

void UNDUpgradeSelector::NativeConstruct()
{
    Super::NativeConstruct();

}

FUpgradeOptionTable UNDUpgradeSelector::GetOption01()
{
    return Option01;
}

FUpgradeOptionTable UNDUpgradeSelector::GetOption02()
{
    return Option02;
}

FUpgradeOptionTable UNDUpgradeSelector::GetOption03()
{
    return Option03;
}
