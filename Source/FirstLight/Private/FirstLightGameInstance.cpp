// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstLightGameInstance.h"

#include "AbilitySystemGlobals.h"

void UFirstLightGameInstance::Init()
{
	Super::Init();

	UAbilitySystemGlobals::Get().InitGlobalData();
}
