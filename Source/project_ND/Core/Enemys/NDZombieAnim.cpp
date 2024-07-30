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

void UNDZombieAnim::AnimNotify_StartATK()
{
	UE_LOG(LogTemp, Warning, TEXT("Start zombie attack"));
}

void UNDZombieAnim::AnimNotify_EndATK()
{
	UE_LOG(LogTemp, Warning, TEXT("End zombie attack"));
}
