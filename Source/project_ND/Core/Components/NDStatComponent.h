// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NDStatComponent.generated.h"


struct FUpgradeOptionTable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_ND_API UNDStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNDStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UNDStatComponent* SetIsWalking  (bool IsWalking  ) { this->bIsWalking   = IsWalking;    return this; }
	UNDStatComponent* SetIsSprinting(bool IsSprinting) { this->bIsSprinting = IsSprinting;  return this; }
	UNDStatComponent* SetIsAttacking(bool IsAttacking) { this->bIsAttacking = IsAttacking;  return this; }
	UNDStatComponent* SetIsCrouched (bool IsCrouched ) { this->bIsCrouched  = IsCrouched;   return this; }

	UNDStatComponent* SetCurHP    (float InCurHP)     { this->CurHP     = InCurHP;     return this; }  
	UNDStatComponent* SetMaxHP    (float InMaxHP)     { this->MaxHP     = InMaxHP;     return this; }  
	UNDStatComponent* SetDamage   (float InDamage)    { this->Damage    = InDamage;    return this; }  
	UNDStatComponent* SetCurHungry(float InCurHungry) { this->CurHungry = InCurHungry; return this; }  
	UNDStatComponent* SetMaxHungry(float InMaxHungry) { this->MaxHungry = InMaxHungry; return this; }

	UNDStatComponent* SetCurHeartbeat(float InCurHeartbeat) { this->CurHeartbeat = InCurHeartbeat; return this; }
	UNDStatComponent* SetMaxHeartbeat(float InMaxHeartbeat) { this->MaxHeartbeat = InMaxHeartbeat; return this; }

	float GetCurHP();       
	float GetMaxHP();       
	float GetDamage();      
	float GetCurHungry();   
	float GetMaxHungry(); 

	float GetCurHeartbeat();
	float GetMaxHeartbeat();

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsWalking   = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsSprinting = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsAttacking = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsCrouched  = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurHP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurHungry;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHungry;

    // next // 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurHeartbeat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHeartbeat;

	void UpgradeStat(FUpgradeOptionTable& Option);

	UPROPERTY(BlueprintReadOnly, Category = "Upgrade Options")
	TArray<FUpgradeOptionTable> UpgradeOptionList;
};
