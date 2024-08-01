// Copyright by project_ND


#include "NDMyCharacter.h"
#include "project_ND/Core/Weapon/NDWeapon.h"
#include "project_ND/Component/NDStatComponent.h"
#include "project_ND/Core/Weapon/NDBluntWeapon.h"

// Sets default values
ANDMyCharacter::ANDMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatComponent = CreateDefaultSubobject<UNDStatComponent>("StatComponent");

}

// Called when the game starts or when spawned
void ANDMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapons();
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
	if (GetCurrentWeapon() != nullptr)
	{
		if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(GetCurrentWeapon()->GetDrawMontage()))
			return;

		if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(GetCurrentWeapon()->GetSheathMontage()))
			return;
	}

	switch (CurWeaponType)
	{
	case EWeaponType::UNARMED:
		CurWeaponType  = InWeaponType;
		NextWeaponType = InWeaponType;

		PlayAnimMontage(GetCurrentWeapon()->GetDrawMontage());
		break;
	default:
		PlayAnimMontage(GetCurrentWeapon()->GetSheathMontage());

		if (CurWeaponType != InWeaponType)
			NextWeaponType = InWeaponType;

		break;
	}
}

void ANDMyCharacter::SpawnWeapons()
{
	FActorSpawnParameters Param;

	Param.Owner = this;

	for (auto& pair : WeaponClasses)
	{
		//GetWorld()->SpawnActor<ANDWeapon>(ANDBluntWeapon::StaticClass()); // Object Reference

		ANDWeapon* weapon = GetWorld()->SpawnActor<ANDWeapon>(pair.Value, Param); // class Reference

		weapon->AttachToHolster(GetMesh());

		Weapons.Add(pair.Key, weapon);
	}
}

float ANDMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);



	if (StatComponent->CurHP)

	return 0.0f;
}