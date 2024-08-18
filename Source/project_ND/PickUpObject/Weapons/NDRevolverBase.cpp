// Copyright by project_ND


#include "NDRevolverBase.h"
#include "project_ND/Core/Characters/NDMyCharacter.h"
#include "project_ND/PickUpObject/Weapons/NDBulletBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Camera/CameraComponent.h"


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

	Param.Owner = this;

	for (uint32 i = 0; i < 30; i++)
	{
		ANDBulletBase* Bullet = GetWorld()->SpawnActor<ANDBulletBase>(BulletClassReference, Param);

		Bullets.Add(Bullet);
	}

	//DamageRate = 1.5f;
}

// Called every frame
void ANDRevolverBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDRevolverBase::OnAttackBegin()
{
	for (auto& Bullet : Bullets)
	{
		if (Bullet->GetIsActive())
			continue;

		UE_LOG(LogTemp, Warning, TEXT("Found an inactive bullet. Firing it now."));

		Bullet->GetProjectile()->Velocity = OwnerCharacter->GetActorForwardVector() * 100000.0f;
		Bullet->SetActorRotation(OwnerCharacter->GetActorRotation());
		Bullet->SetActorLocation(this->GetActorLocation());

		Bullet->SetActive(true);

		break;
	}
}

void ANDRevolverBase::OnAttackEnd()
{
}

