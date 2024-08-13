// Copyright by project_ND


#include "NDUpgradeSelector.h"

#include "Components/Button.h"
#include "Components/Image.h"
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
    if (Option01Image)
    {
        Option01Image->SetRenderScale(FVector2d(1.2));
    }
    
    if (Option02Image)
    {
        Option02Image->SetRenderScale(FVector2d(0.9));
        Option02Image->SetRenderOpacity(0.8);
    }
    
    if (Option03Image)
    {
        Option03Image->SetRenderScale(FVector2d(0.9));
        Option03Image->SetRenderOpacity(0.8);
    }
}

void UNDUpgradeSelector::OnOption02ButtonHovered()
{
    if (Option01Image)
    {
        Option01Image->SetRenderScale(FVector2d(0.9));
        Option01Image->SetRenderOpacity(0.8);
    }
    
    if (Option02Image)
    {
        Option02Image->SetRenderScale(FVector2d(1.2));
    }
    
    if (Option03Image)
    {
        Option03Image->SetRenderScale(FVector2d(0.9));
        Option03Image->SetRenderOpacity(0.8);
    }
}

void UNDUpgradeSelector::OnOption03ButtonHovered()
{
    if (Option01Image)
    {
        Option01Image->SetRenderScale(FVector2d(0.9));
        Option01Image->SetRenderOpacity(0.8);
    }
    
    if (Option02Image)
    {
        Option02Image->SetRenderScale(FVector2d(0.9));
        Option02Image->SetRenderOpacity(0.8);
    }
    
    if (Option03Image)
    {
        Option03Image->SetRenderScale(FVector2d(1.2));
    }
}

void UNDUpgradeSelector::OnOptionUnButtonHovered()
{
    if (Option01Image)
    {
        Option01Image->SetRenderScale(FVector2d(1.0));
        Option01Image->SetRenderOpacity(1.0);
    }
    
    if (Option02Image)
    {
        Option02Image->SetRenderScale(FVector2d(1.0));
        Option02Image->SetRenderOpacity(1.0);
    }
    
    if (Option03Image)
    {
        Option03Image->SetRenderScale(FVector2d(1.0));
        Option03Image->SetRenderOpacity(1.0);
    }
}

void UNDUpgradeSelector::NativeConstruct()
{
    Super::NativeConstruct();

    if (Btn_Op01)
    {
        Btn_Op01->OnHovered.AddDynamic(this, &UNDUpgradeSelector::OnOption01ButtonHovered);
        Btn_Op01->OnUnhovered.AddDynamic(this, &UNDUpgradeSelector::OnOptionUnButtonHovered);
    }

    if (Btn_Op02)
    {
        Btn_Op02->OnHovered.AddDynamic(this, &UNDUpgradeSelector::OnOption02ButtonHovered);
        Btn_Op02->OnUnhovered.AddDynamic(this, &UNDUpgradeSelector::OnOptionUnButtonHovered);
    }
    
    if (Btn_Op03)
    {
        Btn_Op03->OnHovered.AddDynamic(this, &UNDUpgradeSelector::OnOption03ButtonHovered);
        Btn_Op03->OnUnhovered.AddDynamic(this, &UNDUpgradeSelector::OnOptionUnButtonHovered);
    }
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
