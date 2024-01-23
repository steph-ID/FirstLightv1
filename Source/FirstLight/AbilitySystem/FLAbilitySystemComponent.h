// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "FLAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, UFLAbilitySystemComponent*, SourceAsc, float, UnmitigatedDamage, float, MitigatedDamage);
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);

/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API UFLAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	//bool CharacterAbilitiesGiven = false;
	bool bStartupEffectsApplied = false;

	bool bCharacterAbilitiesGiven = false;

	FReceivedDamageDelegate ReceivedDamage;

	virtual void ReceiveDamage(UFLAbilitySystemComponent* SourceAsc, float UnmitigatedDamage, float MitigatedDamage);
	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;

protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
	FActiveGameplayEffectHandle ActiveEffectHandle);
};
