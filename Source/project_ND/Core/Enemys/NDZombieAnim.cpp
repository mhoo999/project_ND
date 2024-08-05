// Copyright by project_ND


#include "NDZombieAnim.h"

#include "project_ND/Enemys/NDZombieBase.h"

void UNDZombieAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	Zombie = Cast<ANDZombieBase>(TryGetPawnOwner());
	
	if (!Zombie)
	{
		UE_LOG(LogTemp, Warning, TEXT("is not initialized"));
	}
}

void UNDZombieAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UNDZombieAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Zombie)
	{
		const FVector Velocity = Zombie->GetVelocity();
		Speed = Velocity.Length();

		bIsAttacking = Zombie->GetIsAttacking();
		bIsDamaged = Zombie->GetIsDamaged();
	}
}

void UNDZombieAnim::PlayZombieAttack()
{
	if (Montage_IsPlaying(AttackAnim))
	{
		return;
	}
	
	Montage_Play(AttackAnim);
}

float UNDZombieAnim::GetZombieAttackPlayTime() const
{
	return Montage_GetPlayRate(AttackAnim);
}

void UNDZombieAnim::AnimNotify_StartAtk()
{
	Zombie->SetTrueAttackTrace();
}

void UNDZombieAnim::AnimNotify_EndAtk()
{
	Zombie->SetFalseAttackTrace();
}

void UNDZombieAnim::AnimNotify_ChangeStateIsAttack()
{
	Zombie->ChangeStateAttack();
}
