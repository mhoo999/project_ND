// Copyright by project_ND


#include "NDEffectComponent.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


UNDEffectComponent::UNDEffectComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNDEffectComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UNDEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UNDEffectComponent::PlayItemUsingEffect(const FVector& Location)
{
	if (ItemUsingSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ItemUsingSound, Location);
	}

	if (ItemUsingWidget)
	{
		
	}
}

void UNDEffectComponent::PlayHitEffect(const FVector& Location)
{
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, Location);
	}
}
