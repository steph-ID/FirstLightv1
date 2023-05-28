// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FirstLightGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API UFirstLightGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;
};
