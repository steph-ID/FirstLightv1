// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "FirstLightPhysicalMaterial.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API UFirstLightPhysicalMaterial : public UPhysicalMaterial
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PhysicalMaterial)
	class USoundBase* FootstepSound = nullptr;
};
