// Copyright by project_ND


#include "NDBluntBase.h"

#include "Kismet/GameplayStatics.h"
#include "project_ND/Core/Characters/NDMyCharacter.h"
#include "Components/ShapeComponent.h"
#include "project_ND/Core/Characters/NDPlayerCharacter.h"
#include "project_ND/Enemys/NDZombieBase.h"
#include "project_ND/Core/Components/NDStatComponent.h"

ANDBluntBase::ANDBluntBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANDBluntBase::BeginPlay()
{
	Super::BeginPlay();
	
	// BodyCollider = Cast<UShapeComponent>(GetComponentByClass(UShapeComponent::StaticClass()));
	// BodyCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// BodyCollider->OnComponentBeginOverlap.AddDynamic(this, &ANDWeaponBase::OnBodyColliderBeginOverlap);

	DamageRate = 1.0f;
}

void ANDBluntBase::BluntSwingSound()
{
	FVector NoiseLocation = this->GetActorLocation();
	
	if (SwingSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SwingSound, GetActorLocation());
	}
}

void ANDBluntBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ANDBluntBase::OnAttackBegin(ANDPlayerCharacter* PlayerCharacter)
{
	// GetBodyCollider()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// GetBodyCollider()->bHiddenInGame = true;
	// bHasApplindDamage = false;

	NDPlayer = PlayerCharacter;
	ANDPlayerCharacter* Player = Cast<ANDPlayerCharacter>(NDPlayer);
	
	Player->StartBluntAttack(this);

	BluntCameraShake(Player);
}

void ANDBluntBase::OnAttackEnd()
{
	// GetBodyCollider()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// GetBodyCollider()->bHiddenInGame = true;

	ANDPlayerCharacter* Player = Cast<ANDPlayerCharacter>(NDPlayer);
	
	Player->EndBluntAttack();
	Player = nullptr;

	// BluntCameraShake(PlayerCharacter);
}

void ANDBluntBase::InitializeBlunt()
{
	// BodyCollider = Cast<UShapeComponent>(GetComponentByClass(UShapeComponent::StaticClass()));
	// BodyCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// BodyCollider->OnComponentBeginOverlap.AddDynamic(this, &ANDWeaponBase::OnBodyColliderBeginOverlap);
}
