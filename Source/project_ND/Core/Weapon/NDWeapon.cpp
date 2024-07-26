// Copyright by project_ND


#include "NDWeapon.h"

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
	
}

// Called every frame
void ANDWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ANDWeapon::Attach(USceneComponent* InParent)
{
	return AttachToComponent
	(
		InParent,
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HolsterSocketName
	);
}

