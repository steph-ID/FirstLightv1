// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FirstLightGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API UFirstLightGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void StartCountdown(float CountdownTime, class AFirstLightArenaGameMode* GameMode); // Will crash multiplayer

	UFUNCTION(BlueprintImplementableEvent)
	void LevelComplete();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowAbilityConfirmCancelText(bool ShowText);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetRespawnCountdown(float RespawnTimeRemaining);


	/**
	* Attribute setters
	*/

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCharacterLevel(int32 CharacterLevel);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetExperience(int32 Experience);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxExperience(int32 Experience);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxHealth(float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentHealth(float CurrentHealth);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetHealthPercentage(float HealthPercentage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetHealthRegenRate(float HealthRegenRate);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxStamina(float MaxStamina);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentStamina(float CurrentStamina);	

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetStaminaPercentage(float StaminaPercentage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetStaminaRegenRate(float StaminaRegenRate);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxMana(float MaxMana);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentMana(float CurrentMana);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetManaPercentage(float ManaPercentage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetManaRegenRate(float ManaRegenRate);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetGold(int32 Gold);
};
