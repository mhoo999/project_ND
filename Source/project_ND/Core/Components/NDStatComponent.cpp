// Copyright by project_ND


#include "NDStatComponent.h"

// Sets default values for this component's properties
UNDStatComponent::UNDStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNDStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNDStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UNDStatComponent::GetCurHP()
{
	return 0.0f;
}

float UNDStatComponent::GetMaxHP()
{
	return 0.0f;
}

float UNDStatComponent::GetDamage()
{
	return 0.0f;
}

float UNDStatComponent::GetCurHungry()
{
	return 0.0f;
}

float UNDStatComponent::GetMaxHungry()
{
	return 0.0f;
}

float UNDStatComponent::GetCurHeartbeat()
{
	return 0.0f;
}

float UNDStatComponent::GetMaxHeartbeat()
{
	return 0.0f;
}