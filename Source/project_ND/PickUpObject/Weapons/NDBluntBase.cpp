// Copyright by project_ND


#include "NDBluntBase.h"

#include "Kismet/GameplayStatics.h"
#include "project_ND/Component/NDStatComponent.h"
#include "project_ND/Core/Characters/NDMyCharacter.h"


// Sets default values
ANDBluntBase::ANDBluntBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANDBluntBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANDBluntBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDBluntBase::OnBodyColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::ApplyDamage
	(
		OtherActor,
		OwnerCharacter->GetStatComponent()->Damage,
		OwnerCharacter->GetController(),
		this,
		nullptr
	);
}

