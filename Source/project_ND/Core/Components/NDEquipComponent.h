// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NDEquipComponent.generated.h"


class ANDMyCharacter;
class ANDPickUpObject;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_ND_API UNDEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNDEquipComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Blunt Slot
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	ANDPickUpObject* FirstSlot;

	// Revolver Slot
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	ANDPickUpObject* SecondSlot;

	// Throwable Slot
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	ANDPickUpObject* ThirdSlot;

	// Lantern Slot
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	ANDPickUpObject* LanternSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slot", meta=(AllowPrivateAccess))
	TSubclassOf<ANDPickUpObject> BasicFirstSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slot", meta=(AllowPrivateAccess))
	TSubclassOf<ANDPickUpObject> BasicSecondSlot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slot", meta=(AllowPrivateAccess))
	TSubclassOf<ANDPickUpObject> BasicThirdSlot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slot", meta=(AllowPrivateAccess))
	TSubclassOf<ANDPickUpObject> BasicLantern;

	UPROPERTY()
	ANDMyCharacter* Player;

	FName FirstSlotSocketName;
	FName SecondSlotSocketName;
	FName ThirdSlotSocketName;
	FName LanternSlotSocketName;

public:
	UFUNCTION(BlueprintCallable)
	void EquipFirstSlot(TSubclassOf<ANDPickUpObject> ItemClass);

	UFUNCTION(BlueprintCallable)
	void EquipSecondSlot(TSubclassOf<ANDPickUpObject> ItemClass);
	
	UFUNCTION(BlueprintCallable)
	void EquipThirdSlot(TSubclassOf<ANDPickUpObject> ItemClass);

	UFUNCTION(BlueprintCallable)
	void EquipLanternSlot(TSubclassOf<ANDPickUpObject> ItemClass);

	ANDPickUpObject* GetFirstSlot();
	ANDPickUpObject* GetSecondSlot();
	ANDPickUpObject* GetThirdSlot();
	ANDPickUpObject* GetLanternSLot();
};
