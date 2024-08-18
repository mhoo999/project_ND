// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NDInputComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_ND_API UNDInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNDInputComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputMappingContext* MappingContext;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* MoveAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* JumpAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* LookAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* WalkAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* SprintAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* CrouchAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* ChangeWeaponAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* ChangeFirstSlot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* ChangeSecondSlot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* ChangeThirdSlot;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* AttackAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* FlashLightOnAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* ChangeCameraAction;

};
