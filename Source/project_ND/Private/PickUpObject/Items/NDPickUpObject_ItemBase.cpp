﻿// Copyright by project_ND


#include "..\..\..\Public\PickUpObject\Items\NDPickUpObject_ItemBase.h"


ANDPickUpObject_ItemBase::ANDPickUpObject_ItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANDPickUpObject_ItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void ANDPickUpObject_ItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANDPickUpObject_ItemBase::InitializeItem(const FItemBaseData& ItemData)
{
	// 하위 클래스에서 생성
}

void ANDPickUpObject_ItemBase::Use()
{
	// 하위 클래스에서 생성
}

