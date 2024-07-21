// Copyright by project_ND


#include "Enemys/NDNormalZombie.h"


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

	ConstructorHelpers::FClassFinder<UAnimInstance> ABP(TEXT("/Script/Engine.AnimBlueprint'/Game/Project_ND/Enemys/ABP_NDNormalZombie.ABP_NDNormalZombie'"));
	if (ABP.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimClass(ABP.Class);
	}
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

