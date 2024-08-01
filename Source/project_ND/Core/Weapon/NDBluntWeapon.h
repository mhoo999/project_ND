// Copyright by project_ND

#pragma once

#include "CoreMinimal.h"
#include "NDWeapon.h"
#include "NDBluntWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ND_API ANDBluntWeapon : public ANDWeapon
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBodyColliderBeginOverlap
	(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);

};