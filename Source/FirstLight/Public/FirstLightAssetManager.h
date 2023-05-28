// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "FirstLightAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API UFirstLightAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	virtual void StartInitialLoading() override;
	
};
