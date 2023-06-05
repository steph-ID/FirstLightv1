// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "FirstLight/FirstLight.h"
#include "FLGameplayAbility.generated.h"

//class AFirstLightCharacter;
class AFirstLightCharacterBase;
/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API UFLGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "First Light|Effects")
	TArray<TSubclassOf<UGameplayEffect>> OngoingEffectsToRemoveOnEnd;
	
	UPROPERTY(EditDefaultsOnly, Category = "First Light|Effects")
	TArray<TSubclassOf<UGameplayEffect>> OngoingEffectsToOnlyApplyOnStart;
	
	TArray<FActiveGameplayEffectHandle> RemoveOnEndEffectHandles;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AFirstLightCharacterBase* GetFirstLightCharacterFromActorInfo() const;
	//AFirstLightCharacter* GetFirstLightCharacterFromActorInfo() const;


public:

	UFLGameplayAbility();

	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "First Light|Abilities")
	EFLAbilityInputID AbilityInputID = EFLAbilityInputID::None;

	// Value to associate an ability with an slot without tying it to an automatically activated input.
	// Passive abilities won't be tied to an input so we need a way to generically associate abilities with slots.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "First Light|Abilities")
	EFLAbilityInputID AbilityID = EFLAbilityInputID::None;

	// Tells an ability to activate immediately when its granted. Used for passive abilities and abilities forced on others.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "First Light|Abilities")
	bool ActivateAbilityOnGranted = false;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	// If an ability is marked as 'ActivateAbilityOnGranted', activate them immediately when given here
	// Epic's comment: Projects may want to initiate passives or do other "BeginPlay" type of logic here.
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
};
