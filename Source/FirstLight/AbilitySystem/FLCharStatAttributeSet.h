#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "FLCharStatAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangeDelegate, const FGameplayAttribute&, Attribute, float, NewValue);

UCLASS()
class FIRSTLIGHT_API UFLCharStatAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UFLCharStatAttributeSet();

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
    FGameplayAttributeData Defense;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Stats")
    FGameplayAttributeData Resist_Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Damage")
    FGameplayAttributeData BaseDamage_Physical;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Damage")
    FGameplayAttributeData BaseDamage_Magic;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Damage")
    FGameplayAttributeData CriticalRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Damage")
    FGameplayAttributeData CriticalMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Speed")
    FGameplayAttributeData Speed_Attack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Speed")
    FGameplayAttributeData Speed_Cast;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|DamageBonus")
    FGameplayAttributeData DamageBonus_Earth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|DamageBonus")
    FGameplayAttributeData DamageBonus_Air;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|DamageBonus")
    FGameplayAttributeData DamageBonus_Fire;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|DamageBonus")
    FGameplayAttributeData DamageBonus_Water;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Resistance")
    FGameplayAttributeData Resist_Earth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Resistance")
    FGameplayAttributeData Resist_Air;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Resistance")
    FGameplayAttributeData Resist_Fire;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Attributes|Resistance")
    FGameplayAttributeData Resist_Water;

    virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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
    void OnRep_Defense(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Resist_Damage(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_BaseDamage_Physical(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_BaseDamage_Magic(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_CriticalRate(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_CriticalMultiplier(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Speed_Attack(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Speed_Cast(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_DamageBonus_Earth(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_DamageBonus_Air(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_DamageBonus_Fire(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_DamageBonus_Water(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Resist_Earth(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Resist_Air(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Resist_Fire(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Resist_Water(const FGameplayAttributeData& OldValue);
};
