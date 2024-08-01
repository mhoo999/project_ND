// Copyright by project_ND


#include "NDZombieBase.h"

#include "Components/CapsuleComponent.h"
#include "project_ND/Core/Enemys/NDAIController.h"
#include "GameFramework/CharacterMovementComponent.h"


ANDZombieBase::ANDZombieBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FClassFinder<ANDAIController> AIController(TEXT("/Script/Engine.Blueprint'/Game/Project_ND/Core/Enemys/AIC_NDAIController.AIC_NDAIController'"));
	if (AIController.Succeeded())
	{
		AIControllerClass = AIController.Class;
	}

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	PerceptionSocket = "head";
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

void ANDZombieBase::SetHitLocationByBoneName(const FName& BoneName)
{
	if (BoneName == "head")
	{
		HitLocation = EHitLocation::Head;
	}
	else if (BoneName == "spine_03" || BoneName == "spine_02" || BoneName == "spine_01")
	{
		HitLocation = EHitLocation::Chest;
	}
	else if (BoneName == "hand_l" || BoneName == "upperarm_twist_01_l" || BoneName == "clavicle_l")
	{
		HitLocation = EHitLocation::LeftArm;
	}
	else if (BoneName == "hand_r" || BoneName == "upperarm_twist_01_r" || BoneName == "clavicle_r")
	{
		HitLocation = EHitLocation::RightArm;
	}
	else if (BoneName == "thigh_l" || BoneName == "calf_l" || BoneName == "foot_l")
	{
		HitLocation = EHitLocation::LeftLeg;
	}
	else if (BoneName == "thigh_r" || BoneName == "calf_r" || BoneName == "foot_r")
	{
		HitLocation = EHitLocation::RightLeg;
	}
	else if (BoneName == "pelvis")
	{
		HitLocation = EHitLocation::Pelvis;
	}
}

void ANDZombieBase::TakeDamage(const float DamageAmount)
{
	HP -= DamageAmount;
}

void ANDZombieBase::Recovery(FString ItemType, const float RecoveryAmount)
{
	HP += RecoveryAmount;
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

float ANDZombieBase::GetMovementSpeed() const
{
	return MovementSpeed;
}

void ANDZombieBase::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	Super::GetActorEyesViewPoint(OutLocation, OutRotation);

	OutLocation = GetMesh()->GetSocketLocation(PerceptionSocket);

	const FRotator SocketRotation = GetMesh()->GetSocketRotation(PerceptionSocket);
	const FRotator AdjustedRotation = SocketRotation + FRotator(120, -120, 0);
	OutRotation = AdjustedRotation;
}

