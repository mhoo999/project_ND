// Copyright by project_ND


#include "..\..\Public\Enemys\NDZombieBase.h"

#include "GameFramework/CharacterMovementComponent.h"


ANDZombieBase::ANDZombieBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HP = InitialHP;
	Damage = AttackDamage;
	Speed = ZombieSpeed;

	GetCharacterMovement()->MaxWalkSpeed = ZombieSpeed;
}

void ANDZombieBase::BeginPlay()
{
	Super::BeginPlay();
}

void ANDZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDZombieBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANDZombieBase::SetHP(float NewHP)
{
	HP = NewHP;
}

void ANDZombieBase::TakeDamage(float DamageAmount)
{
	HP -= DamageAmount;
}

