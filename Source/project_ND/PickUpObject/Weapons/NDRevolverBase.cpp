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

	for (uint32 i = 0; i < MaxBullets; i++)
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
	if (bIsReloading)
	{
		return;
	}

	if (CurBullets <= 0)
	{
		Reload();
		UE_LOG(LogTemp, Warning, TEXT("Reload"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("affter"));

	/*for (auto& Bullet : Bullets)
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

		CurBullets--;

		UE_LOG(LogTemp, Warning, TEXT("Fired! Remaining Bullets: %d"), CurBullets);

		break;

	}*/

	for (auto& Bullet : Bullets)
	{
		if (!Bullet->GetIsActive()) // 비활성화된 총알 찾기
		{
			FRotator ControlRotation = OwnerCharacter->GetControlRotation();
			FVector FireDirection = ControlRotation.Vector();

			Bullet->SetActorRotation(ControlRotation);
			Bullet->SetActorLocation(this->GetActorLocation() + FVector(0.0f, 0.0f, 10.0f)); 
			Bullet->SetActive(true);

			CurBullets--;

			UE_LOG(LogTemp, Warning, TEXT("Fired! Remaining Bullets: %d"), CurBullets);

			break; 
		}
	}


	bHasApplindDamage = false;

	/*for (auto& Bullet : Bullets)
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
		bHasApplindDamage = false;*/
}

void ANDRevolverBase::OnAttackEnd()
{

}

void ANDRevolverBase::Reload()
{
	
	bIsReloading = true;

	// 몽타주 재생
	UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		FOnMontageEnded MontageEndedDelegate;
		MontageEndedDelegate.BindUObject(this, &ANDRevolverBase::OnReloadMontageEnded);

		
		//AnimInstance->Montage_Stop(0.0f);

		AnimInstance->Montage_Play(ReloadMontage);
		AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, ReloadMontage);
	}

	

	UE_LOG(LogTemp, Warning, TEXT("Reloading..."));
}

void ANDRevolverBase::OnReloadMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == ReloadMontage)
	{
		FinishReloading();
		UE_LOG(LogTemp, Warning, TEXT("Reload Complete."));
	}
}

void ANDRevolverBase::FinishReloading()
{
	CurBullets = MaxBullets;
	bIsReloading = false;

	UE_LOG(LogTemp, Warning, TEXT("Reload Complete. Ammo refilled to %d"), CurBullets);
}

bool ANDRevolverBase::IsReloading() const
{
	return bIsReloading;
}

uint32 ANDRevolverBase::GetCurBullets()
{
	return CurBullets;
}

uint32 ANDRevolverBase::GetMaxBullets()
{
	return MaxBullets;
}

