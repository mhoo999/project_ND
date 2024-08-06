﻿// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NDUpgradeSelector.generated.h"

USTRUCT(BlueprintType)
struct FUpgradeOptionTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Options")
	FName OptionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Options")
	FName UpgradeTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Options")
	float UpgradeAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Options")
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Options")
	TSoftObjectPtr<UTexture2D> IconImage;	
};

class UImage;
class ANDPlayerController;
/**
 * 
 */
UCLASS()
class PROJECT_ND_API UNDUpgradeSelector : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	UDataTable* UpgradeOptionTable;

	UPROPERTY(meta=(AllowPrivateAccess, BindWidget))
	UImage* Option01Image;

	UPROPERTY(meta=(AllowPrivateAccess, BindWidget))
	UImage* Option02Image;

	UPROPERTY(meta=(AllowPrivateAccess, BindWidget))
	UImage* Option03Image;

	UPROPERTY(meta=(AllowPrivateAccess))
	FUpgradeOptionTable Option01;

	UPROPERTY(meta=(AllowPrivateAccess))
	FUpgradeOptionTable Option02;

	UPROPERTY(meta=(AllowPrivateAccess))
	FUpgradeOptionTable Option03;

public:
	UFUNCTION(BlueprintCallable)
	void OptionSorting();

	UFUNCTION(BlueprintCallable)
	void ChooseUpgrade(FUpgradeOptionTable Option);

	UFUNCTION(BlueprintCallable)
	FUpgradeOptionTable GetOption01();

	UFUNCTION(BlueprintCallable)
	FUpgradeOptionTable GetOption02();

	UFUNCTION(BlueprintCallable)
	FUpgradeOptionTable GetOption03();
};