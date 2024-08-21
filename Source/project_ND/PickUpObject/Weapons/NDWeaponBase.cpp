// Copyright by project_ND


#include "NDWeaponBase.h"
#include "Components/ShapeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "project_ND/Core/Characters/NDMyCharacter.h"
#include "project_ND/Enemys/NDZombieBase.h"
#include "project_ND/Core/Components/NDStatComponent.h"


ANDWeaponBase::ANDWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANDWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast <ANDMyCharacter>(GetOwner());

	//BodyCollider = Cast<UShapeComponent>(GetComponentByClass(UShapeComponent::StaticClass()));
}

void ANDWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDWeaponBase::Attack()
{
	if(OwnerCharacter && AttackMontage)
	{
		OwnerCharacter->PlayAnimMontage(AttackMontage);
	}
	if (ShootSound)
	{
		UGameplayStatics::PlaySoundAtLocation
		(
			GetWorld(),
			ShootSound,
			GetActorLocation()
		);
	}
}

void ANDWeaponBase::OnAttackBegin()
{
}

void ANDWeaponBase::OnAttackEnd()
{
}


void ANDWeaponBase::OnBodyColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Owner)
		return;

	if (OtherActor == OwnerCharacter)
	{
		return;
	}

	
	if (!bHasApplindDamage)
	{
		if (ANDZombieBase* Zombie = Cast<ANDZombieBase>(OtherActor))
		{
			Zombie->TakeDamage(10.0f * DamageRate, OwnerCharacter, SweepResult);

			bHasApplindDamage = true;
		}

	}

	if (HitEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation
		(
			GetWorld(),
			HitEffect,
			OverlappedComponent->GetComponentTransform()
		);
	}

	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation
		(
			GetWorld(),
			HitSound,
			OverlappedComponent->GetComponentLocation()
		);

		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("dddddd"));
	}

}
