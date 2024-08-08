// Copyright by project_ND


#include "NDStatComponent.h"

#include "NDEffectComponent.h"
#include "project_ND/PickUpObject/NDPickUpObject.h"
#include "project_ND/UI/NDUpgradeSelector.h"

UNDStatComponent::UNDStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNDStatComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* Player = Cast<APawn>(GetOwner());
	EffectComponent = Player->GetComponentByClass<UNDEffectComponent>();
}

void UNDStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ContinuousDecreaseHungry(DeltaTime);
}

float UNDStatComponent::GetCurHP()
{
	return 0.0f;
}

float UNDStatComponent::GetMaxHP()
{
	return 0.0f;
}

float UNDStatComponent::GetDamage()
{
	return 0.0f;
}

float UNDStatComponent::GetCurHungry()
{
	return 0.0f;
}

float UNDStatComponent::GetMaxHungry()
{
	return 0.0f;
}

float UNDStatComponent::GetCurHeartbeat()
{
	return 0.0f;
}

float UNDStatComponent::GetMaxHeartbeat()
{
	return 0.0f;
}

void UNDStatComponent::UpgradeStat(FUpgradeOptionTable& Option)
{
	UpgradeOptionList.Add(Option);
	TArray<FName> StatList = { "MaxHP", "Damage", "MaxHungry" };
	FName UpgradeTo = Option.UpgradeTo;

	if (UpgradeTo == "MaxHP")
	{
		SetMaxHP(MaxHP + Option.UpgradeAmount);
	}
	else if (UpgradeTo == "Damage")
	{
		SetDamage(Damage + Option.UpgradeAmount);
	}
	else if (UpgradeTo == "MaxHungry")
	{
		SetMaxHungry(MaxHungry + Option.UpgradeAmount);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NDStatComponent > UpgradeStat ) Upgrade nothing..."));
	}
}

void UNDStatComponent::TakeDamage(float DamagedAmount)
{
	SetCurHP(CurHP - DamagedAmount);

	APawn* Player = Cast<APawn>(GetOwner());
	EffectComponent->PlayHitEffect(Player->GetActorLocation());
}

void UNDStatComponent::UseItem(FItemBaseData& ItemInfo)
{
	if (ItemInfo.Type == EItemType::HealthPotion)
	{
		SetCurHP(CurHP + ItemInfo.RecoveryAmount);
	}
	else if (ItemInfo.Type == EItemType::Food)
	{
		IncreaseHungry(ItemInfo.RecoveryAmount);
	}
	else
	{
		return;
	}

	APawn* Player = Cast<APawn>(GetOwner());
	EffectComponent->PlayRecoveryEffect(Player->GetActorLocation());
}

void UNDStatComponent::IncreaseHungry(float Amount)
{
	CurHungry += Amount;

	if (CurHungry >= MaxHungry)
	{
		CurHungry = MaxHungry;
	}
}

void UNDStatComponent::DecreaseHungry(float Amount)
{
	CurHungry -= Amount;

	if (CurHungry <= 0)
	{
		CurHP -= Amount;
	}
}

void UNDStatComponent::ContinuousDecreaseHungry(float DeltaSeconds)
{
	float TotalDeltaSeconds = 0.0f;

	TotalDeltaSeconds += DeltaSeconds;

	if (TotalDeltaSeconds >= DeceaseTime)
	{
		if (bIsWalking)
		{
			DecreaseHungry(HungryNormalDecreasePoint);
		}
		else
		{
			DecreaseHungry(HungryRunningDecreasePoint);
		}

		TotalDeltaSeconds = 0.0f;
	}
}

void UNDStatComponent::TemporaryDecreaseHungry()
{
	DecreaseHungry(HungryActionDecreasePoint);
}
