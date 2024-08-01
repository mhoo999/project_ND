// Copyright by project_ND


#include "NDItemBase.h"


ANDItemBase::ANDItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANDItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void ANDItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDItemBase::Use()
{
	// 하위 클래스에서 생성
}

