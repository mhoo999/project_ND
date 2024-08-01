// Copyright by project_ND


#include "NDWeaponBase.h"

#include "Components/ShapeComponent.h"
#include "project_ND/Core/Characters/NDMyCharacter.h"


// Sets default values
ANDWeaponBase::ANDWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANDWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast <ANDMyCharacter>(GetOwner());

	BodyCollider = Cast<UShapeComponent>(GetComponentByClass(UShapeComponent::StaticClass()));
	//BodyCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called every frame
void ANDWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ANDWeaponBase::AttachToHolster(USceneComponent* InParent)
{
	return AttachToComponent
	(
		InParent,
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HolsterSocketName
	);
}

bool ANDWeaponBase::AttachToHand(USceneComponent* InParent)
{
	return AttachToComponent
	(
		InParent,
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		EquipSocketName
	);
}

void ANDWeaponBase::Attack()
{
	OwnerCharacter->PlayAnimMontage(AttackMontage);
}

