// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstLightCharacterBase.h"
#include "FirstLightEnemy.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API AFirstLightEnemy : public AFirstLightCharacterBase
{
	GENERATED_BODY()

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
