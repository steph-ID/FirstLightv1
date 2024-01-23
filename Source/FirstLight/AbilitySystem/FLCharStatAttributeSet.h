#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "FLAttributeSet.h"
#include "FLCharStatAttributeSet.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangeDelegate, const FGameplayAttribute&, Attribute, float, NewValue);

UCLASS()
class FIRSTLIGHT_API UFLCharStatAttributeSet : public UFLAttributeSet
{
    GENERATED_BODY()

public:
    UFLCharStatAttributeSet();
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Stats")
    FGameplayAttributeData Strength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Stats")
    FGameplayAttributeData Dexterity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Stats")
    FGameplayAttributeData Intelligence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Stats")
    FGameplayAttributeData Haste;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Stats")
    FGameplayAttributeData Vitality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Stats")
    FGameplayAttributeData Endurance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Stats")
    FGameplayAttributeData Precision;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Speed")
    FGameplayAttributeData Speed_Attack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Speed")
    FGameplayAttributeData Speed_Cast;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Damage")
    FGameplayAttributeData Critical_Rate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Damage")
    FGameplayAttributeData Critical_Multiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Damage")
    FGameplayAttributeData BaseDamage_Physical;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Damage")
    FGameplayAttributeData BaseDamage_Ranged;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Damage")
    FGameplayAttributeData BaseDamage_Magic;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|DamageBonus")
    FGameplayAttributeData DamageBonus_Earth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|DamageBonus")
    FGameplayAttributeData DamageBonus_Air;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|DamageBonus")
    FGameplayAttributeData DamageBonus_Fire;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|DamageBonus")
    FGameplayAttributeData DamageBonus_Water;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Stats", ReplicatedUsing = OnRep_Armor)
    FGameplayAttributeData Armor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Stats")
    FGameplayAttributeData Defense;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Stats")
    FGameplayAttributeData Resist_Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Resistance")
    FGameplayAttributeData Resist_Earth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Resistance")
    FGameplayAttributeData Resist_Air;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Resistance")
    FGameplayAttributeData Resist_Fire;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Resistance")
    FGameplayAttributeData Resist_Water;

    /**
     * Attribute Accessors
     */

    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Strength);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Dexterity);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Intelligence);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Haste);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Vitality);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Endurance);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Precision);
    
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Speed_Attack);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Speed_Cast);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Critical_Rate);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Critical_Multiplier);
    
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, BaseDamage_Physical);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, BaseDamage_Ranged);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, BaseDamage_Magic);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, DamageBonus_Earth);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, DamageBonus_Air);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, DamageBonus_Fire);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, DamageBonus_Water);
    
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Armor);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Defense);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Resist_Damage);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Resist_Earth);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Resist_Air);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Resist_Fire);
    ATTRIBUTE_ACCESSORS(UFLCharStatAttributeSet, Resist_Water);

protected:

    // OnRep functions
    UFUNCTION()
    void OnRep_Strength(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Dexterity(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Intelligence(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Haste(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Vitality(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Endurance(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Precision(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Speed_Attack(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Speed_Cast(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_BaseDamage_Physical(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_BaseDamage_Ranged(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_BaseDamage_Magic(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_DamageBonus_Earth(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_DamageBonus_Air(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_DamageBonus_Fire(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_DamageBonus_Water(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Critical_Rate(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Critical_Multiplier(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Armor(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Defense(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Resist_Damage(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Resist_Earth(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Resist_Air(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Resist_Fire(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Resist_Water(const FGameplayAttributeData& OldValue);
};
