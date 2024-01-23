// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "FLAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API UFLAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UFLAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
		
	/*UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_CharacterLevel)
	FGameplayAttributeData CharacterLevel;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_XP)
	FGameplayAttributeData XP;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_MaxXP)
	FGameplayAttributeData MaxXP;*/

	/**
	 * Vital Attributes
	 */
	
	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
		
	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_HealthRegenRate)
	FGameplayAttributeData HealthRegenRate;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_ManaRegenRate)
	FGameplayAttributeData ManaRegenRate;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_StaminaRegenRate)
	FGameplayAttributeData StaminaRegenRate;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_MovementSpeed)
	FGameplayAttributeData MovementSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_MaxMovementSpeed)
	FGameplayAttributeData MaxMovementSpeed;

	/**
	 * XP & Gold Attributes
	*/

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_Gold)
	FGameplayAttributeData Gold;
		
	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_XPBounty)
	FGameplayAttributeData XPBounty;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_GoldBounty)
	FGameplayAttributeData GoldBounty;

	/**
	 * Arena Attributes
	 */
			
	UPROPERTY(BlueprintReadOnly, Category = "First Light|Arena", ReplicatedUsing = OnRep_ArenaLevel)
	FGameplayAttributeData ArenaLevel;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Arena", ReplicatedUsing = OnRep_ArenaXP)
	FGameplayAttributeData ArenaXP;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Arena", ReplicatedUsing = OnRep_ArenaMaxXP)
	FGameplayAttributeData ArenaMaxXP;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Arena", ReplicatedUsing = OnRep_ArenaScore)
	FGameplayAttributeData ArenaScore;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Arena", ReplicatedUsing = OnRep_ArenaTopScore)
	FGameplayAttributeData ArenaTopScore;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Arena", ReplicatedUsing = OnRep_ArenaKills)
	FGameplayAttributeData ArenaKills;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Arena", ReplicatedUsing = OnRep_ArenaAssists)
	FGameplayAttributeData ArenaAssists;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Arena", ReplicatedUsing = OnRep_ArenaDeaths)
	FGameplayAttributeData ArenaDeaths;
	
	/**
	 * Meta Attributes
	*/
		
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData IncomingDamage;
	
	UPROPERTY(BlueprintReadOnly, Category = "Rewards")
	FGameplayAttributeData IncomingXP;
	
	UPROPERTY(BlueprintReadOnly, Category = "Rewards")
	FGameplayAttributeData IncomingArenaXP;
		
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;

	/**
	 * Attribute Accessors
	 */
		
	/*ATTRIBUTE_ACCESSORS(UFLAttributeSet, CharacterLevel);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, XP);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, MaxXP);*/
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, HealthRegenRate);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, MaxMana);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, ManaRegenRate);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, Stamina);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, MaxStamina);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, StaminaRegenRate);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, MovementSpeed);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, MaxMovementSpeed);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, Gold);

	/**
	 * Arena Attribute Accessors
	 */
		
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, ArenaLevel);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, ArenaXP);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, ArenaMaxXP);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, ArenaScore);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, ArenaTopScore);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, ArenaKills);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, ArenaAssists);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, ArenaDeaths);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, XPBounty);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, GoldBounty);
	
	/**
	 * Meta Attribute Accessors
	 */
		
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, IncomingDamage);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, IncomingXP);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, IncomingArenaXP);
	ATTRIBUTE_ACCESSORS(UFLAttributeSet, Damage);

protected:

	/**
	 * Default character functions
	*/

	/*UFUNCTION()
	void OnRep_CharacterLevel(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_XP(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_MaxXP(const FGameplayAttributeData& OldValue) const;*/
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_HealthRegenRate(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_ManaRegenRate(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_StaminaRegenRate(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_MaxMovementSpeed(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Gold(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_XPBounty(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_GoldBounty(const FGameplayAttributeData& OldValue) const;


	/**
	 * Arena functions
	 */
	
	UFUNCTION()
	void OnRep_ArenaLevel(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_ArenaXP(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_ArenaMaxXP(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_ArenaScore(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_ArenaTopScore(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_ArenaKills(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_ArenaDeaths(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_ArenaAssists(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_Damage(const FGameplayAttributeData& OldValue) const;

private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
