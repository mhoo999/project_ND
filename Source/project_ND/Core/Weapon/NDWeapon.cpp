// Copyright by project_ND


#include "NDWeapon.h"
#include "/Project/project_ND/Source/project_ND/Core/Characters/NDPlayerCharacter.h"
#include "Components/ShapeComponent.h"

// Sets default values
ANDWeapon::ANDWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANDWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast <ANDMyCharacter>(GetOwner());

	BodyCollider = Cast<UShapeComponent>(GetComponentByClass(UShapeComponent::StaticClass()));
	//BodyCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called every frame
void ANDWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ANDWeapon::AttachToHolster(USceneComponent* InParent)
{
	return AttachToComponent
	(
		InParent,
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HolsterSocketName
	);
}

bool ANDWeapon::AttachToHand(USceneComponent* InParent)
{
	return AttachToComponent
	(
		InParent,
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		EquipSocketName
	);
}

void ANDWeapon::Attack()
{
	OwnerCharacter->PlayAnimMontage(AttackMontage);
}

