// Copyright by project_ND


#include "../../Public/Enemys/NDZombieBase.h"

#include "Core/Enemys/NDAIController.h"
#include "GameFramework/CharacterMovementComponent.h"


ANDZombieBase::ANDZombieBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	AIControllerClass = ANDAIController::StaticClass();
}

void ANDZombieBase::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeZombie();
}

void ANDZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDZombieBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ANDZombieBase::GetHP() const
{
	return HP;
}

void ANDZombieBase::SetHP(float NewHP)
{
	HP = NewHP;
}

void ANDZombieBase::TakeDamage(float DamageAmount)
{
	HP -= DamageAmount;
}

void ANDZombieBase::InitializeZombie()
{
	HP										= InitialHP;
	GetCharacterMovement()->MaxWalkSpeed	= MovementSpeed;
	Damage									= AttackDamage;
	Range									= AttackRange;
}

float ANDZombieBase::GetAttackRange() const
{
	return AttackRange;
}

