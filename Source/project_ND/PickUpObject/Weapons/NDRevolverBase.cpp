// Copyright by project_ND


#include "NDRevolverBase.h"
#include "project_ND/Core/Characters/NDMyCharacter.h"
#include "project_ND/PickUpObject/Weapons/NDBulletBase.h"


// Sets default values
ANDRevolverBase::ANDRevolverBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANDRevolverBase::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters Param;

	Param.Owner = OwnerCharacter;

	for (uint32 i = 0; i < 30; i++)
	{
		ANDBulletBase* Bullet = GetWorld()->SpawnActor<ANDBulletBase>(BulletClassReference, Param);

		Bullets.Add(Bullet);
	}

	 
	
	/*FActorSpawnParameters Param;
	
	Param.Owner = OwnerCharacter;

	
	Bullet = GetWorld()->SpawnActor<AActor>(BulletClassReference, Param);
	
	Bullet->AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		BulletEquipSocketName
	);*/
}

// Called every frame
void ANDRevolverBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDRevolverBase::OnAttackBegin()
{
}

void ANDRevolverBase::OnAttackEnd()
{
}

