// Copyright by project_ND


#include "NDEffectComponent.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "project_ND/UI/NDRecoveryMask.h"
#include "project_ND/UI/NDHitMask.h"


UNDEffectComponent::UNDEffectComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNDEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Cast<ACharacter>(GetOwner())->GetController());

	if (PlayerController)
	{
		if (RecoveryWidgetClass)
		{
			RecoveryWidget = CreateWidget<UNDRecoveryMask>(PlayerController, RecoveryWidgetClass);
			RecoveryWidget->AddToViewport();
			RecoveryWidget->SetVisibility(ESlateVisibility::Hidden);
		}

		if (HitWidgetClass)
		{
			HitWidget = CreateWidget<UNDHitMask>(PlayerController, HitWidgetClass);
			HitWidget->AddToViewport();
			HitWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UNDEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UNDEffectComponent::PlayRecoveryEffect(const FVector& Location)
{
	if (RecoverySound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), RecoverySound, Location);
	}

	if (RecoveryWidget)
	{
		RecoveryWidget->SetVisibility(ESlateVisibility::Visible);
		RecoveryWidget->ShowRecoveryMask();
	}
}

void UNDEffectComponent::PlayHitEffect(const FVector& Location)
{
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, Location);
	}

	if (HitWidget)
	{
		HitWidget->SetVisibility(ESlateVisibility::Visible);
		HitWidget->ShowHitMask();
	}
}
