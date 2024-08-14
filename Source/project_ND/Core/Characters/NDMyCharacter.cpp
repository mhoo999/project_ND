// Copyright by project_ND


#include "NDMyCharacter.h"

#include "project_ND/Core/Components/NDEffectComponent.h"
#include "project_ND/Core/Components/NDEquipComponent.h"
#include "project_ND/Core/Components/NDStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "project_ND/Core/Characters/NDPlayerController.h"


// Sets default values
ANDMyCharacter::ANDMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatComponent = CreateDefaultSubobject<UNDStatComponent>(TEXT("StatComponent"));
	EffectComponent = CreateDefaultSubobject<UNDEffectComponent>(TEXT("Effect Component"));
	EquipComponent = CreateDefaultSubobject<UNDEquipComponent>(TEXT("Equip Component"));
}

// Called when the game starts or when spawned
void ANDMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentEquipmentSlot = EEquipment::UNARMED;
	// SpawnWeapons();
}

// Called every frame
void ANDMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANDMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANDMyCharacter::ChangeWeapon(EWeaponType InWeaponType)
{
	if (GetCurrentPickUpObject() != nullptr)
	{
		if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(GetCurrentPickUpObject()->GetDrawMontage()))
			return;

		if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(GetCurrentPickUpObject()->GetSheathMontage()))
			return;
	}

	switch (CurPickUpObjectType)
	{
	case EWeaponType::UNARMED:
		CurPickUpObjectType  = InWeaponType;
		NextPickUpObjectType = InWeaponType;

		PlayAnimMontage(GetCurrentPickUpObject()->GetDrawMontage());
		break;
	default:
		PlayAnimMontage(GetCurrentPickUpObject()->GetSheathMontage());

		if (CurPickUpObjectType != InWeaponType)
			NextPickUpObjectType = InWeaponType;

		break;
	}
}

ANDPickUpObject* ANDMyCharacter::GetCurrentEquipmentItem()
{
	return CurrentEquipmentItem;
}

EEquipment ANDMyCharacter::GetCurrentEquipmentSlot()
{
	return CurrentEquipmentSlot;
}

void ANDMyCharacter::SpawnWeapons()
{
	// FActorSpawnParameters Param;
	//
	// Param.Owner = this;
	//
	// for (auto& pair : PickUpObjectClasses)
	// {
	// 	//GetWorld()->SpawnActor<ANDWeapon>(ANDBluntWeapon::StaticClass()); // Object Reference
	//
	// 	ANDPickUpObject* weapon = GetWorld()->SpawnActor<ANDPickUpObject>(pair.Value, Param); // class Reference
	//
	// 	weapon->AttachToHolster(GetMesh());
	//
	// 	PickUpObjects.Add(pair.Key, weapon);
	// }
}

void ANDMyCharacter::TakeDamage(float DamageAmount, AActor* Attacker, FHitResult HitResult)
{
	if (bIsDead)
	{
		return;
	}

	StatComponent->TakeDamage(DamageAmount);

	UE_LOG(LogTemp, Log, TEXT("%s HP : %f"), *GetName(), StatComponent->GetCurHP());


	if (StatComponent->GetCurHP() > 0)
	{
	
		if (HitMontage)
		{
			PlayAnimMontage(HitMontage);
		}

		if (OnPlayerDamaged.IsBound())
		{
			OnPlayerDamaged.Broadcast();
		}
	}
	else
	{
		bIsDead = true;

		if (DeathMontage)
		{
			PlayAnimMontage(DeathMontage);

			GetCharacterMovement()->DisableMovement();

			if (OnPlayerDamaged.IsBound())
			{
				OnPlayerDamaged.Broadcast();
			}

			ANDPlayerController* PlayerController = Cast<ANDPlayerController>(GetController());
			if (PlayerController)
			{
				PlayerController->SetIgnoreMoveInput(true);
				PlayerController->SetIgnoreLookInput(true);
			}

			ShowDeathScreen();
		}
	}
}

void ANDMyCharacter::Recovery(FString ItemType, float RecoveryAmount)
{
	
}


//void ANDMyCharacter::Die()
//{
//
//	UE_LOG(LogTemp, Warning, TEXT("%s has died!"), *GetName());
//}

/*
* float ANDMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	StatComponent->SetCurHP(StatComponent->CurHP - DamageAmount);

	//UE_LOG(LogTemp, Log, TEXT("%s HP : %f"), GetName(), StatComponent->CurHP);

	if (StatComponent->CurHP > 0)
		PlayAnimMontage(HitMontage);
	else
		PlayAnimMontage(DeathMontage);

	return 0.0f;
}
*/

