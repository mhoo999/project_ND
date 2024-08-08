﻿// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NDEffectComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_ND_API UNDEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNDEffectComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sound", meta=(AllowPrivateAccess))
	USoundBase* ItemUsingSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sound", meta=(AllowPrivateAccess))
	TSubclassOf<UUserWidget> ItemUsingWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hit", meta=(AllowPrivateAccess))
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sound", meta=(AllowPrivateAccess))
	TSubclassOf<UUserWidget> HitWidget;
	
public:
	void PlayItemUsingEffect(const FVector& Location);

	void PlayHitEffect(const FVector& Location);
	
};
