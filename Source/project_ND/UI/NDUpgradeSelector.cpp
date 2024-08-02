// Copyright by project_ND


#include "NDUpgradeSelector.h"

#include "Kismet/GameplayStatics.h"

void UNDUpgradeSelector::ChooseUpgrade()
{
	// PlayerState 접근하여 기능 업그레이드
	
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}
