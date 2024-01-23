// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstLight/AbilitySystem/FLAbilitySystemComponent.h"

void UFLAbilitySystemComponent::ReceiveDamage(UFLAbilitySystemComponent* SourceAsc,
	float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.Broadcast(SourceAsc, UnmitigatedDamage, MitigatedDamage);
}

void UFLAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UFLAbilitySystemComponent::EffectApplied);
}

void UFLAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}
