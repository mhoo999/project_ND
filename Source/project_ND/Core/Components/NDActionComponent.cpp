// Copyright by project_ND


#include "NDActionComponent.h"


UNDActionComponent::UNDActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UNDActionComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UNDActionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UNDActionComponent::StartResist()
{
}

