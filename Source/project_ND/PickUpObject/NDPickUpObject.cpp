// Copyright by project_ND


#include "NDPickUpObject.h"
#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"
#include "project_ND/Core/Characters/NDMyCharacter.h"


ANDPickUpObject::ANDPickUpObject()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	SetRootComponent(ItemMesh);
	ItemMesh->SetCollisionProfileName(TEXT("IgnoreOnlyPawn"));
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetRelativeScale3D(FVector(50.f));

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ANDPickUpObject::OnBoxBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ANDPickUpObject::OnBoxEndOverlap);
}

void ANDPickUpObject::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast <ANDMyCharacter>(GetOwner());

	BodyCollider = Cast<UShapeComponent>(GetComponentByClass(UShapeComponent::StaticClass()));
}

void ANDPickUpObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsInPlayer)
	{
		ScanPlayer();
	}
}

void ANDPickUpObject::OnAttackBegin(ANDPlayerCharacter* Player)
{
}

void ANDPickUpObject::OnAttackEnd()
{
}

void ANDPickUpObject::OnPickedUp()
{
	if(OwnerCharacter)
		OwnerCharacter->PlayAnimMontage(AttackMontage);
}

void ANDPickUpObject::SetItemMesh(UStaticMesh* Mesh) const
{
	ItemMesh->SetStaticMesh(Mesh);
}

void ANDPickUpObject::InitializeItem(const FItemBaseData& ItemData)
{
	ItemID = ItemData.ItemID;
	ItemName = ItemData.ItemName;
	ItemType = ItemData.Type;
	RecoveryAmount = ItemData.RecoveryAmount;
	DamageAmount = ItemData.DamageAmount;
	
	if (ItemData.ItemMesh)
	{
		SetItemMesh(ItemData.ItemMesh);
	}

	ItemThumbnail = ItemData.ItemThumbnail;
	Description = ItemData.Description;
	bIsEmpty = ItemData.bNotUse;
}

bool ANDPickUpObject::AttachToHolster(USceneComponent* InParent)
{
	return AttachToComponent
	(
		InParent,
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HolsterSocketName
	);
}

bool ANDPickUpObject::AttachToHand(USceneComponent* InParent)
{
	return AttachToComponent
	(
		InParent,
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		EquipSocketName
	);
}

void ANDPickUpObject::SetSimulate()
{
	ItemMesh->SetSimulatePhysics(true);
}

float ANDPickUpObject::GetDamageAmount()
{
	return DamageAmount;
}

void ANDPickUpObject::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsEquip == true)
	{
		return;
	}

	NDPlayer = Cast<ANDMyCharacter>(OtherActor);
	if (NDPlayer)
	{
		bIsInPlayer = true;
	}
}

void ANDPickUpObject::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (NDPlayer == Cast<ANDMyCharacter>(OtherActor))
	{
		ItemMesh->SetRenderCustomDepth(false);
		bIsInPlayer = false;
		NDPlayer = nullptr;
	}
}

void ANDPickUpObject::ScanPlayer()
{
	FVector PlayerLocation = NDPlayer->GetActorLocation();
	
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
							
	GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), PlayerLocation, ECC_Visibility, Params);
	// DrawDebugLine(GetWorld(), GetActorLocation(), PlayerLocation, FColor::Yellow, false, 5.f, 0, 2.f);

	if (Cast<ANDMyCharacter>(HitResult.GetActor()))
	{
		ItemMesh->SetRenderCustomDepth(true);
	}
}

void ANDPickUpObject::bIsEquipToggle()
{
	bIsEquip = !bIsEquip;
}

bool ANDPickUpObject::GetEquip()
{
	return bIsEquip;
}

void ANDPickUpObject::SetRenderCustomDepthFalse()
{
	ItemMesh->SetRenderCustomDepth(false);
}

UStaticMeshComponent* ANDPickUpObject::GetItemMeshComponent()
{
	return ItemMesh;
}

void ANDPickUpObject::SphereComponentOverlapEventClear()
{
	SphereComponent->OnComponentBeginOverlap.Clear();
	SphereComponent->OnComponentEndOverlap.Clear();
	SphereComponent->DestroyComponent();
	SphereComponent = nullptr;
}
