// Copyright by project_ND


#include "NDBluntBase.h"

#include "Kismet/GameplayStatics.h"
#include "project_ND/Core/Characters/NDMyCharacter.h"
#include "Components/ShapeComponent.h"
#include "project_ND/Enemys/NDZombieBase.h"
#include "project_ND/Core/Components/NDStatComponent.h"




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
	
	BodyCollider->OnComponentBeginOverlap.AddDynamic(this, &ANDBluntBase::OnBodyColliderBeginOverlap);
		
}

// Called every frame
void ANDBluntBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDBluntBase::OnBodyColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Target = Cast<ANDZombieBase>(OtherActor);
	
	if(Target)
		Target->TakeDamage(10);

	//UGameplayStatics::ApplyDamage
	//(
	//	OtherActor,
	//	Target = Cast<ANDZombieBase>(OtherActor);
	//	Target->TakeDamage(10)->Damage,
	//	Target->GetController(),
	//	OwnerCharacter->GetStatComponent()->Damage,
	//	OwnerCharacter->GetController(),
	//	this,
	//	nullptr
	//);
}

