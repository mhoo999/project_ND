// Copyright by project_ND


#include "NDBluntWeapon.h"
#include "Components/ShapeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "project_ND/Core/Characters/NDMyCharacter.h"
#include "project_ND/Component/NDStatComponent.h"

void ANDBluntWeapon::BeginPlay()
{
	Super::BeginPlay();

	BodyCollider->OnComponentBeginOverlap.AddDynamic(this, &ANDBluntWeapon::OnBodyColliderBeginOverlap);
}

void ANDBluntWeapon::OnBodyColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::ApplyDamage
	(
		OtherActor,
		OwnerCharacter->GetStatComponent()->Damage,
		OwnerCharacter->GetController(),
		this,
		nullptr
	);
}
