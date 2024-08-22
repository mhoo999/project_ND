// Copyright by project_ND


#include "NDZombieBase.h"

#include "Components/AudioComponent.h"
#include "project_ND/Core/Enemys/NDAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "project_ND/Core/Characters/NDMyCharacter.h"
#include "project_ND/Core/Enemys/NDZombieAnim.h"
#include "project_ND/Core/Components/NDStatComponent.h"


ANDZombieBase::ANDZombieBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<ANDAIController> AIController(TEXT("/Game/Project_ND/Core/Enemys/AIC_NDAIController"));
	if (AIController.Succeeded())
	{
		AIControllerClass = AIController.Class;
	}

	IdleAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Idle Audio Component"));
	ExcitementAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Excitement Audio Component"));
	EatingAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Eating Audio Component"));
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	PerceptionSocket = "pelvis";
	
	TraceRadius = 20.0f;
	TraceLength = 100.0f;
}

void ANDZombieBase::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeZombie();
}

void ANDZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAttackTrace)
	{
		PerformHandSphereTraces();
	}
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

void ANDZombieBase::TakeDamage(const float DamageAmount, AActor* Attacker, FHitResult HitResult)
{
	ANDAIController* AIController = Cast<ANDAIController>(GetController());
	PlayGetHitSound();
	
	HP -= DamageAmount;
	
	if (HP <= 0)
	{
		AIController->SetAIState("Dead");
	}
	else
	{
		// AIController->GetDamaged(HitResult.Location);
		AIController->SetAIState("Stunned");
		UNDZombieAnim* ZombieAnim = Cast<UNDZombieAnim>(GetMesh()->GetAnimInstance());
		ZombieAnim->PlayDamagedAnim();
	}
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

	const FRotator SocketRotation = FRotator(0, GetMesh()->GetSocketRotation(PerceptionSocket).Yaw, 0);
	const FRotator AdjustedRotation = SocketRotation + FRotator(0, 90, 0);
	OutRotation = AdjustedRotation;
}

void ANDZombieBase::PerformHandSphereTraces()
{
	FVector LeftHandLocation = GetMesh()->GetSocketLocation(FName("hand_l"));
	FVector RightHandLocation = GetMesh()->GetSocketLocation(FName("hand_r"));

	FVector LeftHandEnd = LeftHandLocation + GetMesh()->GetForwardVector() * TraceLength;
	FVector RightHandEnd = RightHandLocation + GetMesh()->GetForwardVector() * TraceLength;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FHitResult LeftHitResult;
	bool bLeftHit = GetWorld()->SweepSingleByChannel(LeftHitResult, LeftHandLocation, LeftHandEnd, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(TraceRadius),CollisionParams);

	if (bLeftHit)
	{
		bIsAttackTrace = false;
		ANDMyCharacter* Player = Cast<ANDMyCharacter>(LeftHitResult.GetActor());
		if (Player)
		{
			// UE_LOG(LogTemp, Warning, TEXT("Left hand hit player"));
			Player->TakeDamage(Damage, this, LeftHitResult);
			UE_LOG(LogTemp, Warning, TEXT("NDZombieBase) MyDamage : %f, player HP : %f"), Damage, Player->GetStatComponent()->CurHP);
		}
	}

	FHitResult RightHitResult;
	bool bRightHit = GetWorld()->SweepSingleByChannel(RightHitResult, RightHandLocation, RightHandEnd, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(TraceRadius),CollisionParams);

	if (bRightHit)
	{
		bIsAttackTrace = false;
		ANDMyCharacter* Player = Cast<ANDMyCharacter>(RightHitResult.GetActor());
		if (Player)
		{
			// UE_LOG(LogTemp, Warning, TEXT("Right hand hit player"));
			Player->TakeDamage(Damage, this, RightHitResult);
			UE_LOG(LogTemp, Warning, TEXT("NDZombieBase) MyDamage : %f, player HP : %f"), Damage, Player->GetStatComponent()->CurHP);
		}
	}
}

bool ANDZombieBase::GetIsAttacking() const
{
	return bIsAttacking;
}

bool ANDZombieBase::GetIsDamaged() const
{
	return bIsDamaged;
}

void ANDZombieBase::ChangeStateAttack()
{
	bIsAttacking = !bIsAttacking;
	UNDZombieAnim* ZombieAnim = Cast<UNDZombieAnim>(GetMesh()->GetAnimInstance());
	ZombieAnim->bIsAttacking = bIsAttacking;
}

void ANDZombieBase::ChangeStateDamaged()
{
	bIsDamaged = !bIsDamaged;
	UNDZombieAnim* ZombieAnim = Cast<UNDZombieAnim>(GetMesh()->GetAnimInstance());
	ZombieAnim->bIsDamaged = bIsDamaged;
}

void ANDZombieBase::SetTrueAttackTrace()
{
	bIsAttackTrace = true;
}

void ANDZombieBase::SetFalseAttackTrace()
{
	bIsAttackTrace = false;
}

void ANDZombieBase::PlayDeathAnim()
{
	if (DeathAnimation)
	{
		GetMesh()->PlayAnimation(DeathAnimation, false);
	}
}

void ANDZombieBase::PlayIdleAudio()
{
	if (IdleAudioComponent && !IdleAudioComponent->IsPlaying())
	{
		IdleAudioComponent->Play();
	}
}

void ANDZombieBase::PlayExcitementAudio()
{
	if (ExcitementAudioComponent && !ExcitementAudioComponent->IsPlaying())
	{
		ExcitementAudioComponent->Play();
	}
}

void ANDZombieBase::PlayEatingAudio()
{
	if (EatingAudioComponent && !EatingAudioComponent->IsPlaying())
	{
		EatingAudioComponent->Play();
	}
}

void ANDZombieBase::PlayAttackSound()
{
	if (AttackSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), AttackSound, GetActorLocation(), GetActorRotation());
	}
}

void ANDZombieBase::PlayGetHitSound()
{
	if (GetHitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), GetHitSound, GetActorLocation(), GetActorRotation());
	}
}

void ANDZombieBase::PlayDieSound()
{
	if (DieSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DieSound, GetActorLocation(), GetActorRotation());
	}
}

void ANDZombieBase::StopAllSounds()
{
	if (IdleAudioComponent && IdleAudioComponent->IsPlaying())
	{
		IdleAudioComponent->Stop();
	}
	if (ExcitementAudioComponent && ExcitementAudioComponent->IsPlaying())
	{
		ExcitementAudioComponent->Stop();
	}
	if (EatingAudioComponent && EatingAudioComponent->IsPlaying())
	{
		EatingAudioComponent->Stop();
	}
}
