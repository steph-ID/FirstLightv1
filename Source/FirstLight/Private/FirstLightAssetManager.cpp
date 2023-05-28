// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstLightAssetManager.h"
#include "AbilitySystemGlobals.h"

void UFirstLightAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}