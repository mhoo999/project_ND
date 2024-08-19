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

	MaxBullets = 6;
	CurBullets = MaxBullets;
	bIsReloading = false;
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


	DamageRate = 2.0f;
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

		
		FRotator ControlRotation = OwnerCharacter->GetControlRotation();
		FVector FireDirection = ControlRotation.Vector();

		Bullet->GetProjectile()->Velocity = OwnerCharacter->GetActorForwardVector() * 100.0f;
		Bullet->SetActorRotation(OwnerCharacter->GetControlRotation());
		Bullet->SetActorLocation(this->GetActorLocation());

		FVector MuzzleLocation = this->GetActorLocation() + FVector(0.0f, 0.0f, 10.0f);
		Bullet->SetActorLocation(MuzzleLocation);

		Bullet->SetActive(true);

		break;
		
	}
		bHasApplindDamage = false;
}

void ANDRevolverBase::OnAttackEnd()
{

}

void ANDRevolverBase::Reload()
{
	FOnMontageEnded MontageEndedDelegate;
	MontageEndedDelegate.BindUObject(this, &ANDRevolverBase::OnReloadMontageEnded);

	if (!bIsReloading && ReloadMontage)
	{
		bIsReloading = true;

		UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(ReloadMontage);
			AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, ReloadMontage);
		}
	}

}

void ANDRevolverBase::OnReloadMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == ReloadMontage)
	{
		FinishReloading();
	}
}

void ANDRevolverBase::FinishReloading()
{
	CurBullets = MaxBullets;
	bIsReloading = false;

	UE_LOG(LogTemp, Warning, TEXT("Reload Complete. Ammo refilled to %d"), CurBullets);
}

