// Copyright by project_ND


#include "NDBluntWeapon.h"
#include "Components/ShapeComponent.h"

void ANDBluntWeapon::BeginPlay()
{
	Super::BeginPlay();

	BodyCollider->OnComponentBeginOverlap.AddDynamic(this, &ANDBluntWeapon::OnBodyColliderBeginOverlap);
}

void ANDBluntWeapon::OnBodyColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
