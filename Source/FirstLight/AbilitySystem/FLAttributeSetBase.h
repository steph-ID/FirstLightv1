// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "FLAttributeSetBase.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API UFLAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	
	UFLAttributeSetBase();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	/**
	 * Vital Attributes
	 */
		
	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_CharacterLevel)
	FGameplayAttributeData CharacterLevel;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_XP)
	FGameplayAttributeData XP;

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_MaxXP)
	FGameplayAttributeData MaxXP;
	
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

	UPROPERTY(BlueprintReadOnly, Category = "First Light|Character Attributes", ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;

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
		
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;

	/**
	 * Attribute Accessors
	 */
		
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, CharacterLevel);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, XP);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, MaxXP);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, Health);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, MaxHealth);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, HealthRegenRate);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, Mana);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, MaxMana);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, ManaRegenRate);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, Stamina);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, MaxStamina);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, StaminaRegenRate);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, MovementSpeed);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, MaxMovementSpeed);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, Armor);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, Gold);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, ArenaLevel);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, ArenaXP);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, ArenaMaxXP);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, ArenaScore);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, ArenaTopScore);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, ArenaKills);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, ArenaAssists);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, ArenaDeaths);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, XPBounty);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, GoldBounty);
	
	// Attribute Accessors for Meta Attributes
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, IncomingDamage);
	ATTRIBUTE_ACCESSORS(UFLAttributeSetBase, Damage);

	void AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute,
									 const FGameplayAttributeData& MaxAttribute, float NewMaxValue,
									 const FGameplayAttribute& AffectedAttributeProperty) const;

protected:

	/**
	 * Default character functions
	 */

	UFUNCTION()
	virtual void OnRep_CharacterLevel(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_XP(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MaxXP(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_HealthRegenRate(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_ManaRegenRate(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_StaminaRegenRate(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MovementSpeed(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MaxMovementSpeed(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Armor(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Gold(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_XPBounty(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_GoldBounty(const FGameplayAttributeData& OldValue);


	/**
	 * Arena functions
	 */
	
	UFUNCTION()
	virtual void OnRep_ArenaLevel(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_ArenaXP(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_ArenaMaxXP(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_ArenaScore(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_ArenaTopScore(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_ArenaKills(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_ArenaDeaths(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_ArenaAssists(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& OldValue);
	
private:
	FGameplayTag HitDirectionFrontTag;
	FGameplayTag HitDirectionBackTag;
	FGameplayTag HitDirectionRightTag;
	FGameplayTag HitDirectionLeftTag;
};
