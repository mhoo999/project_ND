// Copyright by project_ND


#include "NDWeapon.h"
#include "project_ND/Core/Characters/NDPlayerCharacter.h"

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
	
	Character = Cast <APlayerCharacter>(GetOwner());
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
	Character->PlayAnimMontage(AttackMontage);
}

