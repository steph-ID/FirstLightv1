// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstLightGameTypes.generated.h"

USTRUCT(BlueprintType)
struct FCharacterData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="First Light|Ability System")
	TArray<TSubclassOf<class UGameplayEffect>> Effects;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="First Light|Ability System")
	TArray<TSubclassOf<class UGameplayAbility>> Abilities;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="First Light|Animation")
	class UCharacterAnimDataAsset* CharacterAnimDataAsset = nullptr;
};

USTRUCT(BlueprintType)
struct FCharacterAnimationData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly)
	class UBlendSpace* MovementBlendSpace = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	class UAnimSequenceBase* IdleAnimationAsset = nullptr;
};

UENUM(BlueprintType)
enum class EFoot : uint8
{
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right")
};
