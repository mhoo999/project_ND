// Copyright by project_ND


#include "NDTestPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "project_ND/Enemys/NDZombieBase.h"
#include "project_ND/PickUpObject/Items/NDPickUpObject_ItemBase_Throwable.h"


ANDTestPawn::ANDTestPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(MeshComponent);

	auto MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true;

	Club = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Club Component"));
	Club->SetupAttachment(RootComponent);
	Club->SetRelativeLocation(FVector(150.0f, 50.0f, 0.0f));
	Club->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	Club->SetRelativeScale3D(FVector(0.25f, 0.25f, 1.5f));
	Club->SetCollisionProfileName(TEXT("Projectile"));
	Club->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ANDTestPawn::BeginPlay()
{
	Super::BeginPlay();
	
	Club->OnComponentBeginOverlap.AddDynamic(this, &ANDTestPawn::OnCollisionComponentBeginOverlap);
}

void ANDTestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CameraRotation = CameraComponent->GetComponentRotation();
	MeshComponent->SetWorldRotation(CameraRotation);
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
	PlayerInputComponent->BindAxis("SetClubLeft", this, &ANDTestPawn::SetClubLeft);
	PlayerInputComponent->BindAxis("SetClubRight", this, &ANDTestPawn::SetClubRight);
	PlayerInputComponent->BindAxis("Attack", this, &ANDTestPawn::Attack);
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

void ANDTestPawn::SetClubLeft(float Value)
{
	if (Value != 0.0)
	{
		bClubLeft = true;
		Club->SetRelativeLocation(FVector(150.0f, -50.0f, 0.0f));
		Club->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	}
}

void ANDTestPawn::SetClubRight(float Value)
{
	if (Value != 0.0)
	{
		bClubLeft = false;
		Club->SetRelativeLocation(FVector(150.0f, 50.0f, 0.0f));
		Club->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	}
}

void ANDTestPawn::Attack(float Value)
{
	if (Value != 0.0)
	{
		if (!bAttacking)
		{
			Club->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
		
			FTimerHandle AttackHandle;
			GetWorld()->GetTimerManager().ClearTimer(AttackHandle);
			GetWorld()->GetTimerManager().SetTimer(AttackHandle, FTimerDelegate::CreateLambda([&]
			{
				if (bClubLeft)
				{
					Club->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
				}
				else
				{
					Club->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
				}
				
				bAttacking = false;
			}), 0.2f, false);
		}
	}
}

void ANDTestPawn::OnCollisionComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner())
	{
		return;
	}

	if (ANDZombieBase* HitZombie = Cast<ANDZombieBase>(OtherActor))
	{
		HitZombie->SetHitLocationByBoneName(SweepResult.BoneName);
		HitZombie->TakeDamage(10.0f);
		
		UE_LOG(LogTemp, Warning, TEXT("Hit Location : %s"), *SweepResult.BoneName.ToString());
	}
}
