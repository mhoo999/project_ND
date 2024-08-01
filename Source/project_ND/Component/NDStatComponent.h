// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NDStatComponent.generated.h"


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
	float CurHP     = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHP     = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage    = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurHungry = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHungry = 0;

    // next // 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurHeartbeat = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHeartbeat = 0;

};
