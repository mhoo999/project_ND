// Copyright by project_ND


#include "NDBulletBase.h"
#include "Components/ShapeComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "project_ND/PickUpObject/Weapons/NDRevolverBase.h"
#include "project_ND/Enemys/NDZombieBase.h"


// Sets default values
ANDBulletBase::ANDBulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TrailEffects = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailEffect"));
	SetRootComponent(TrailEffects);

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Collider->SetupAttachment(TrailEffects);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

// Called when the game starts or when spawned
void ANDBulletBase::BeginPlay()
{
	Super::BeginPlay();

	SetActive(false);

	ANDRevolverBase* Revolver = Cast<ANDRevolverBase>(GetOwner());

	Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Collider->OnComponentBeginOverlap.AddDynamic(this,     &ANDBulletBase::OnBodyColliderBeginOverlap);
	// Collider->OnComponentBeginOverlap.AddDynamic(Revolver, &ANDWeaponBase::OnBodyColliderBeginOverlap);
}

// Called every frame
void ANDBulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDBulletBase::SetActive(bool IsActive)
{
	bIsActive = IsActive;

	if (bIsActive)
	{
		SetActorHiddenInGame(false);
		

		Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		ProjectileMovement->Velocity = GetActorForwardVector() * BulletSpeed;
		ProjectileMovement->bSimulationEnabled = true; //isActive == 

		TrailEffects->Activate(true);

		//Add
		GetWorld()->GetTimerManager().SetTimer(LifespanTimerHandle, this, &ANDBulletBase::DestroyBullet, BulletLifespan, false);
	}
	else
	{
		SetActorHiddenInGame(true);

		Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		ProjectileMovement->Velocity = FVector::ZeroVector;
		ProjectileMovement->bSimulationEnabled = false; 

		TrailEffects->Deactivate();

		//Add
		GetWorld()->GetTimerManager().ClearTimer(LifespanTimerHandle);
	}
}

void ANDBulletBase::DestroyBullet()
{
	SetActive(false);
}

void ANDBulletBase::OnBodyColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ANDRevolverBase* Revolver = Cast<ANDRevolverBase>(GetOwner());

	if (OtherActor == Revolver)
		return;

	if (OtherActor == Revolver->GetOwner())
		return;

	FHitResult HitResult;
	if (ANDZombieBase* ZombieBase = Cast<ANDZombieBase>(OtherActor))
	{
		ZombieBase->TakeDamage(30.0f, this, HitResult);
	}
	
	SetActive(false);
}


