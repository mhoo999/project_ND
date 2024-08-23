// Copyright by project_ND


#include "NDThrowableBase.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Hearing.h"
#include "project_ND/Core/Characters/NDMyCharacter.h"


ANDThrowableBase::ANDThrowableBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->OnComponentHit.AddDynamic(this, &ANDThrowableBase::OnHit);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	ProjectileMovementComponent->bAutoActivate = false;
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->MaxSpeed = 1000.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 10.0f;
}

void ANDThrowableBase::BeginPlay()
{
	Super::BeginPlay();
}

void ANDThrowableBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bCanNoise && OtherActor != Cast<ANDMyCharacter>(OtherActor))
	{
		// Make noise code
		FVector NoiseLocation = this->GetActorLocation();
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), NoiseLocation, 1.0f, this);
		// UE_LOG(LogTemp, Warning, TEXT("Make Noise : %lld.%lld.%lld"), FMath::TruncToInt(NoiseLocation.X), FMath::TruncToInt(NoiseLocation.Y), FMath::TruncToInt(NoiseLocation.Z));
		
		if (BreakSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, BreakSound, GetActorLocation());
		}

		bCanNoise = false;
		GetWorld()->GetTimerManager().SetTimer(NoiseTimerHandle, FTimerDelegate::CreateLambda([&]
		{
			bCanNoise = true;
		}), 10.0f, false);
	}
}

void ANDThrowableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDThrowableBase::Use()
{
	Super::Use();

	
}

