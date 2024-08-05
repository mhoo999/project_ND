// Copyright by project_ND


#include "NDUpgradeSelector.h"

#include "Components/Image.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void UNDUpgradeSelector::OptionSorting()
{
	if (UpgradeOptionTable)
	{
		static const FString ContextString(TEXT("OptionSorting"));
		TArray<FUpgradeOptionTable*> Options;
		UpgradeOptionTable->GetAllRows<FUpgradeOptionTable>(ContextString, Options);

		TSet<int32> SelectedIndices;
		while (SelectedIndices.Num() < 3 && SelectedIndices.Num() < Options.Num())
		{
			int32 RandomIndex = FMath::RandRange(0, Options.Num() - 1);
			SelectedIndices.Add(RandomIndex);
		}

		TArray<UImage*> OptionImages = { Option01, Option02, Option03 };
		int32 Index = 0;

		for (auto SelectedIndex : SelectedIndices)
		{
			if (Options.IsValidIndex(SelectedIndex) && OptionImages.IsValidIndex(Index))
			{
				UTexture2D* SelectedTexture = Options[SelectedIndex]->Image;
				
				if (SelectedTexture && OptionImages[Index])
				{
					OptionImages[Index]->SetBrushFromTexture(SelectedTexture);
				}
				
				Index++;
			}
		}
	}
}

void UNDUpgradeSelector::ChooseUpgrade()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		// PlayerState 접근하여 기능 업그레이드
		// if (APlayerState* PlayerState = PlayerController->GetPlayerState<>())
		
		
		// UI 숨기기 & 게임 재개
		if (AHUD* PlayerHUD = PlayerController->GetHUD())
		{
			
		}
	}
	
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}
