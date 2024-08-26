// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NDStatComponent.generated.h"


struct FItemBaseData;
class UNDEffectComponent;
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

	UFUNCTION(BlueprintCallable)
	float GetCurHP();       

	UFUNCTION(BlueprintCallable)
	float GetMaxHP();       


	float GetDamage();      
	
	UFUNCTION(BlueprintCallable)
	float GetCurHungry(); 

	UFUNCTION(BlueprintCallable)
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
	float CurHP = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHP = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurHungry = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHungry = 0.0f;

    // next // 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurHeartbeat = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHeartbeat = 0.0f;

	void UpgradeStat(FUpgradeOptionTable Option);

	UPROPERTY(BlueprintReadOnly, Category = "Upgrade Options")
	TArray<FUpgradeOptionTable> UpgradeOptionList;

private:
	UPROPERTY()
	UNDEffectComponent* EffectComponent;

public:
	void TakeDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void UseItem(FItemBaseData ItemInfo);

	UFUNCTION(BlueprintCallable)
	void IncreaseHungry(float Amount);

	UFUNCTION(BlueprintCallable)
	void DecreaseHungry(float Amount);

private:
	// 기본 배고픔 감소 수치
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hungry", meta=(AllowPrivateAccess))
	float HungryNormalDecreasePoint;

	// 달릴 때 배고픔 감수 수치
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hungry", meta=(AllowPrivateAccess))
	float HungryRunningDecreasePoint;

	// 감소되는 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hungry", meta=(AllowPrivateAccess))
	float DeceaseTime;

	// 큰 동작시 배고픔 감수 수치 (공격, 점프)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hungry", meta=(AllowPrivateAccess))
	float HungryActionDecreasePoint;

	void ContinuousDecreaseHungry(float DeltaSeconds);

	void TemporaryDecreaseHungry();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DEF;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MoveSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AttackSpeed;

	UFUNCTION(BlueprintCallable)
	void SetDamageAmount(float DamageAmount);
};
