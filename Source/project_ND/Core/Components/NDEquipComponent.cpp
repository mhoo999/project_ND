// Copyright by project_ND


#include "NDEquipComponent.h"

#include "project_ND/Core/Characters/NDMyCharacter.h"


UNDEquipComponent::UNDEquipComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	FirstSlotSocketName		= TEXT("BluntWeapon_Holster");
	SecondSlotSocketName	= TEXT("RevolverWeapon_Holster");
	ThirdSlotSocketName		= TEXT("Throwable_Holster");
	LanternSlotSocketName	= TEXT("FlashLight_Holster");
}

void UNDEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ANDMyCharacter>(GetOwner());
	
	if (BasicLantern)
	{
		EquipLanternSlot(BasicLantern);
	}

	if (BasicFirstSlotItem)
	{
		EquipFirstSlot(BasicFirstSlotItem);
	}

	if (BasicSecondSlotItem)
	{
		EquipSecondSlot(BasicSecondSlotItem);
	}

	if (BasicThirdSlotItem)
	{
		EquipThirdSlot(BasicThirdSlotItem);
	}
}

void UNDEquipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UNDEquipComponent::EquipFirstSlot(TSubclassOf<ANDPickUpObject> ItemClass)
{
	if (FirstSlot)
	{
		FirstSlot->Destroy();
		FirstSlot = nullptr;
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Player;
	SpawnParams.Instigator = Player->GetInstigator();

	FirstSlot = GetWorld()->SpawnActor<ANDPickUpObject>(ItemClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	if (FirstSlot)
	{
		FirstSlot->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), FirstSlotSocketName);
	}
}

void UNDEquipComponent::EquipSecondSlot(TSubclassOf<ANDPickUpObject> ItemClass)
{
	if (SecondSlot)
	{
		SecondSlot->Destroy();
		SecondSlot = nullptr;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Player;
	SpawnParams.Instigator = Player->GetInstigator();

	SecondSlot = GetWorld()->SpawnActor<ANDPickUpObject>(ItemClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	if (SecondSlot)
	{
		SecondSlot->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), SecondSlotSocketName);
	}
}

void UNDEquipComponent::EquipThirdSlot(TSubclassOf<ANDPickUpObject> ItemClass)
{
	if (ThirdSlot)
	{
		ThirdSlot->Destroy();
		ThirdSlot = nullptr;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Player;
	SpawnParams.Instigator = Player->GetInstigator();

	ThirdSlot = GetWorld()->SpawnActor<ANDPickUpObject>(ItemClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	if (ThirdSlot)
	{
		ThirdSlot->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), ThirdSlotSocketName);
	}
}

void UNDEquipComponent::EquipLanternSlot(TSubclassOf<ANDPickUpObject> ItemClass)
{
	if (LanternSlot)
	{
		LanternSlot->Destroy();
		LanternSlot = nullptr;
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Player;
	SpawnParams.Instigator = Player->GetInstigator();

	LanternSlot = GetWorld()->SpawnActor<ANDPickUpObject>(ItemClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	if (LanternSlot)
	{
		LanternSlot->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), LanternSlotSocketName);
	}
}

ANDPickUpObject* UNDEquipComponent::GetFirstSlot()
{
	if (FirstSlot == nullptr)
	{
		return nullptr;
	}
	
	return FirstSlot;
}

ANDPickUpObject* UNDEquipComponent::GetSecondSlot()
{
	if (SecondSlot == nullptr)
	{
		return nullptr;
	}
	
	return SecondSlot;
}

ANDPickUpObject* UNDEquipComponent::GetThirdSlot()
{
	if (ThirdSlot == nullptr)
	{
		return nullptr;
	}
	
	return ThirdSlot;
}

ANDPickUpObject* UNDEquipComponent::GetLanternSLot()
{
	if (LanternSlot == nullptr)
	{
		return nullptr;
	}
	
	return LanternSlot;
}
