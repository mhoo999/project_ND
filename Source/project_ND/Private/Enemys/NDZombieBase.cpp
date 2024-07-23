// Copyright by project_ND


#include "..\..\Public\Enemys\NDZombieBase.h"

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
}

void ANDZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDZombieBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ANDZombieBase::GetHP()
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

float ANDZombieBase::GetHearingAbility() const
{
	return HearingAbility;
}

float ANDZombieBase::GetSightAbility() const
{
	return SightAbility;
}

float ANDZombieBase::GetMovementSpeed() const
{
	return MovementSpeed;
}

void ANDZombieBase::InitializeZombie()
{
	HP = InitialHP;
}

