// Copyright by project_ND


#include "TestPawn/NDTestPawn.h"

#include "GameFramework/FloatingPawnMovement.h"


ANDTestPawn::ANDTestPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(MeshComponent);

	auto MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));
}

void ANDTestPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANDTestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDTestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ANDTestPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANDTestPawn::MoveRight);
}

void ANDTestPawn::MoveForward(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Move Forward"));
	
	if (Value != 0.0)
	{
		AddMovementInput(FVector::ForwardVector, Value);
	}
}

void ANDTestPawn::MoveRight(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Move Right"));
	
	if (Value != 0.0)
	{
		AddMovementInput(FVector::RightVector, Value);
	}
}

