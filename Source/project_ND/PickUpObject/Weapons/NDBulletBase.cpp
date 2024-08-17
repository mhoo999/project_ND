// Copyright by project_ND


#include "NDBulletBase.h"
#include "Components/ShapeComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ANDBulletBase::ANDBulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailEffect"));
	TrailEffect->SetupAttachment(RootComponent);

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Collider->SetupAttachment(TrailEffect);

	

}

// Called when the game starts or when spawned
void ANDBulletBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANDBulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

