// Copyright by project_ND


#include "NDWeaponBase.h"

#include "Components/ShapeComponent.h"
#include "project_ND/Core/Characters/NDMyCharacter.h"


ANDWeaponBase::ANDWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANDWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast <ANDMyCharacter>(GetOwner());

	BodyCollider = Cast<UShapeComponent>(GetComponentByClass(UShapeComponent::StaticClass()));
}

void ANDWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDWeaponBase::Attack()
{
	OwnerCharacter->PlayAnimMontage(AttackMontage);
}

