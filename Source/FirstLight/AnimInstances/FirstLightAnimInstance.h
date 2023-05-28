// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FirstLightAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API UFirstLightAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	class UBlendSpace* GetLocomotionBlendSpace() const;

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	class UAnimSequenceBase* GetIdleAnimation() const;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Animation")
	class UCharacterAnimDataAsset* DefaultCharacterAnimDataAsset;
	
};
