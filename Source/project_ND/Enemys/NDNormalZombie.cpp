// Copyright by project_ND


#include "NDNormalZombie.h"


ANDNormalZombie::ANDNormalZombie()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshObject(TEXT("/Script/Engine.SkeletalMesh'/Game/Project_ND/Resource/Zombies/zombie.zombie'"));
	if (SkeletalMeshObject.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMeshObject.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}

	InitialHP		= 100.0f;
	MovementSpeed	= 100.0f;
	AttackDamage	= 10.0f;
	AttackRange		= 200.0f;
}

void ANDNormalZombie::BeginPlay()
{
	Super::BeginPlay();
}

void ANDNormalZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDNormalZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

