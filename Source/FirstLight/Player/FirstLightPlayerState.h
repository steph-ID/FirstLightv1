// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "FirstLight/AbilitySystem/FLAttributeSetBase.h"
#include "FirstLightPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*StatValue*/)

/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API AFirstLightPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AFirstLightPlayerState();
	
	// Ability System
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFLAttributeSetBase* GetAttributeSetBase() const;
	
	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState")
	AFirstLightPlayerController* GetFirstLightPlayerController() const;

	/*UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState")
	UFLAbilitySystemComponent* GetFLAbilitySystemComponent() const { return AbilitySystemComponent; }*/

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|UI")
	void ShowAbilityConfirmCancelText(bool ShowText);

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState")
	bool IsAlive() const;

	/**
	* Leveling up
	*/
	
	FOnPlayerStatChanged OnCharacterLevelChangedDelegate;
	FOnPlayerStatChanged OnArenaXPChangedDelegate;
	FOnPlayerStatChanged OnArenaLevelChangedDelegate;

	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	FORCEINLINE int32 GetArenaLevel() const { return ArenaLevel; }
	FORCEINLINE int32 GetArenaXP() const { return ArenaXP; }

	void AddToArenaXP(int32 IncomingArenaXP);
	void AddToArenaLevel(int32 IncomingArenaLevel);
	
	void SetArenaXP(int32 IncomingArenaXP);
	void SetArenaLevel(int32 IncomingArenaLevel);

	/**
	* Getters for attributes from AttributeSetBase. Returns Current Value unless otherwise specified.
	*/

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	int32 GetXP() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	int32 GetMaxXP() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	float GetHealthRegenRate() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	float GetMaxMana() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	float GetManaRegenRate() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	float GetStamina() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	float GetMaxStamina() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	float GetStaminaRegenRate() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	float GetMovementSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	float GetMaxMovementSpeed() const;

	//UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	//float GetArmor() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	int32 GetGold() const;

	//--- Arena attributes
	
	/*UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	int32 GetArenaLevel() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	int32 GetArenaXP() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	int32 GetArenaMaxXP() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	int32 GetArenaScore() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	int32 GetArenaTopScore() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	int32 GetArenaKills() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	int32 GetArenaDeaths() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|PlayerState|Attributes")
	int32 GetArenaAssists() const;*/

protected:
	
	/*UPROPERTY()
	class UFLAbilitySystemComponent* AbilitySystemComponent;*/

	UPROPERTY()
	class UFLAttributeSetBase* AttributeSetBase;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	/*UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;*/
	
private:
	
	// Override BeginPlay
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_ArenaLevel)
	int32 ArenaLevel = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_ArenaXP)
	int32 ArenaXP = 0;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_ArenaLevel(int32 OldArenaLevel) const;

	UFUNCTION()
	void OnRep_ArenaXP(int32 OldArenaXP) const;

	FGameplayTag DeadTag;

	FDelegateHandle CharacterLevelChangedDelegateHandle;
	FDelegateHandle XPChangedDelegateHandle;
	FDelegateHandle MaxXPChangedDelegateHandle;
	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle HealthRegenRateChangedDelegateHandle;
	FDelegateHandle ManaChangedDelegateHandle;
	FDelegateHandle MaxManaChangedDelegateHandle;
	FDelegateHandle ManaRegenRateChangedDelegateHandle;
	FDelegateHandle StaminaChangedDelegateHandle;
	FDelegateHandle MaxStaminaChangedDelegateHandle;
	FDelegateHandle StaminaRegenRateChangedDelegateHandle;
	FDelegateHandle MovementSpeedChangedDelegateHandle;
	FDelegateHandle MaxMovementSpeedChangedDelegateHandle;
	FDelegateHandle ArmorChangedDelegateHandle;
	FDelegateHandle GoldChangedDelegateHandle;
	FDelegateHandle ArenaLevelChangedDelegateHandle;
	FDelegateHandle ArenaXPChangedDelegateHandle;
	FDelegateHandle ArenaMaxXPChangedDelegateHandle;
	FDelegateHandle ArenaScoreChangedDelegateHandle;
	FDelegateHandle ArenaTopScoreChangedDelegateHandle;
	FDelegateHandle ArenaKillsChangedDelegateHandle;
	FDelegateHandle ArenaDeathsChangedDelegateHandle;
	FDelegateHandle ArenaAssistsChangedDelegateHandle;

	/**
	* Attribute changed callbacks
	*/
	
	virtual void CharacterLevelChanged(const FOnAttributeChangeData& Data);
	virtual void XPChanged(const FOnAttributeChangeData& Data);
	virtual void MaxXPChanged(const FOnAttributeChangeData& Data);
	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void HealthRegenRateChanged(const FOnAttributeChangeData& Data);
	virtual void ManaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxManaChanged(const FOnAttributeChangeData& Data);
	virtual void ManaRegenRateChanged(const FOnAttributeChangeData& Data);
	virtual void StaminaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void StaminaRegenRateChanged(const FOnAttributeChangeData& Data);
	virtual void MovementSpeedChanged(const FOnAttributeChangeData& Data);
	virtual void MaxMovementSpeedChanged(const FOnAttributeChangeData& Data);
	virtual void ArmorChanged(const FOnAttributeChangeData& Data);
	virtual void GoldChanged(const FOnAttributeChangeData& Data);
	virtual void ArenaLevelChanged(const FOnAttributeChangeData& Data);
	virtual void ArenaXPChanged(const FOnAttributeChangeData& Data);
	virtual void ArenaMaxXPChanged(const FOnAttributeChangeData& Data);
	virtual void ArenaScoreChanged(const FOnAttributeChangeData& Data);
	virtual void ArenaTopScoreChanged(const FOnAttributeChangeData& Data);
	virtual void ArenaKillsChanged(const FOnAttributeChangeData& Data);
	virtual void ArenaDeathsChanged(const FOnAttributeChangeData& Data);
	virtual void ArenaAssistsChanged(const FOnAttributeChangeData& Data);

	// Tag change callbacks
	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
};
