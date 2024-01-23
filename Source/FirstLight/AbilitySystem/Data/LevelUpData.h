// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpData.generated.h"

USTRUCT(BlueprintType)
struct FFLLevelUpData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 NextLevelXPRequirement = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 AttributePointAward = 1;

	UPROPERTY(EditDefaultsOnly)
	int32 SpellPointAward = 1;
};


/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API ULevelUpData : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly)
	TArray<FFLLevelUpData> LevelUpData;

	int32 FindLevelForXP(int32 XP);
};
