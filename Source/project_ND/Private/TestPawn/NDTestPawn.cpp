// Copyright by project_ND


#include "TestPawn/NDTestPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PickUpObject/Items/NDPickUpObject_ItemBase_Throwable.h"


ANDTestPawn::ANDTestPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(MeshComponent);

	auto MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true;
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
	PlayerInputComponent->BindAxis("Turn", this, &ANDTestPawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ANDTestPawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MoveUp", this, &ANDTestPawn::MoveUp);
	PlayerInputComponent->BindAxis("SpawnThrowableItem", this, &ANDTestPawn::SpawnThrowable);
}

void ANDTestPawn::MoveForward(float Value)
{
	if (Value != 0.0)
	{
		FVector Forward = CameraComponent->GetForwardVector();
		AddMovementInput(Forward, Value);
	}
}

void ANDTestPawn::MoveRight(float Value)
{
	if (Value != 0.0)
	{
		FVector Right = CameraComponent->GetRightVector();
		AddMovementInput(Right, Value);
	}
}

void ANDTestPawn::MoveUp(float Value)
{
	if (Value != 0.0)
	{
		FVector Up = CameraComponent->GetUpVector();
		AddMovementInput(Up, Value);
	}
}

void ANDTestPawn::SpawnThrowable(float Value)
{
	if (Value != 0.0 && TestItem && bCanSpawn)
	{
		FTransform ThrowPosition = CameraComponent->GetComponentTransform();
		FRotator SpawnRotation = CameraComponent->GetComponentRotation();

		ANDPickUpObject_ItemBase_Throwable* ThrowableItem = GetWorld()->SpawnActor<ANDPickUpObject_ItemBase_Throwable>(TestItem, ThrowPosition);
		if (ThrowableItem)
		{
			FVector LauchDirection = SpawnRotation.Vector();
			ThrowableItem->ProjectileMovementComponent->Velocity = LauchDirection * ThrowableItem->ProjectileMovementComponent->InitialSpeed;
			ThrowableItem->ProjectileMovementComponent->Activate();

			bCanSpawn = false;
			GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, FTimerDelegate::CreateLambda([&]
			{
				bCanSpawn = true;
			}), 1, true);
		}
	}
}
