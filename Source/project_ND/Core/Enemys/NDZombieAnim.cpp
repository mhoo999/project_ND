// Copyright by project_ND


#include "NDZombieAnim.h"

#include "project_ND/Enemys/NDZombieBase.h"

void UNDZombieAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	ZombieBase = Cast<ANDZombieBase>(TryGetPawnOwner());
}

void UNDZombieAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (ZombieBase)
	{
		const FVector Velocity = ZombieBase->GetVelocity();
		Speed = Velocity.Length();
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
	UE_LOG(LogTemp, Warning, TEXT("Start zombie attack"));
}

void UNDZombieAnim::AnimNotify_EndAtk()
{
	UE_LOG(LogTemp, Warning, TEXT("End zombie attack"));
}
