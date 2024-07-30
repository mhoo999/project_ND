// Copyright by project_ND


#include "NDPickUpObject_ItemBase_Throwable.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Hearing.h"


ANDPickUpObject_ItemBase_Throwable::ANDPickUpObject_ItemBase_Throwable()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->OnComponentHit.AddDynamic(this, &ANDPickUpObject_ItemBase_Throwable::OnHit);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	ProjectileMovementComponent->bAutoActivate = false;
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->MaxSpeed = 1000.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 10.0f;
}

void ANDPickUpObject_ItemBase_Throwable::BeginPlay()
{
	Super::BeginPlay();
}

void ANDPickUpObject_ItemBase_Throwable::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bCanNoise)
	{
		FVector NoiseLocation = this->GetActorLocation();
		// Make noise code
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), NoiseLocation, 1.0f, this);
		UE_LOG(LogTemp, Warning, TEXT("Make Noise : %lld.%lld.%lld"), FMath::TruncToInt(NoiseLocation.X), FMath::TruncToInt(NoiseLocation.Y), FMath::TruncToInt(NoiseLocation.Z));
		
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

void ANDPickUpObject_ItemBase_Throwable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDPickUpObject_ItemBase_Throwable::Use()
{
	Super::Use();

	
}

