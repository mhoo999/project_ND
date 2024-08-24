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
}

void ANDPickUpObject::OnAttackBegin()
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

	if (ANDMyCharacter* Player = Cast<ANDMyCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("OnBoxBeginOverlap"));
		
		ItemMesh->SetRenderCustomDepth(true);
	}
}

void ANDPickUpObject::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ANDMyCharacter* Player = Cast<ANDMyCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("OnBoxEndOverlap"));
		
		ItemMesh->SetRenderCustomDepth(false);
	}
}

void ANDPickUpObject::bIsEquipTrue()
{
	bIsEquip = true;
}
