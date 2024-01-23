// Fill out your copyright notice in the Description page of Project Settings.


#include "FLCharStatAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UFLCharStatAttributeSet::UFLCharStatAttributeSet()
{
}

void UFLCharStatAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
}

void UFLCharStatAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Strength, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Haste, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Vitality, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Endurance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Precision, COND_None, REPNOTIFY_Always);
    
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Speed_Attack, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Speed_Cast, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Critical_Rate, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Critical_Multiplier, COND_None, REPNOTIFY_Always);
    
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, BaseDamage_Physical, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, BaseDamage_Ranged, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, BaseDamage_Magic, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, DamageBonus_Earth, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, DamageBonus_Air, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, DamageBonus_Fire, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, DamageBonus_Water, COND_None, REPNOTIFY_Always);
    
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Armor, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Defense, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Resist_Damage, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Resist_Earth, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Resist_Air, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Resist_Fire, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UFLCharStatAttributeSet, Resist_Water, COND_None, REPNOTIFY_Always);
}

void UFLCharStatAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Strength, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Dexterity, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Intelligence, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Haste(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Haste, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Vitality(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Vitality, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Endurance(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Endurance, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Precision(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Precision, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Speed_Attack(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Speed_Attack, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Speed_Cast(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Speed_Cast, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Critical_Rate(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Critical_Rate, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Critical_Multiplier(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Critical_Multiplier, OldValue);
}

void UFLCharStatAttributeSet::OnRep_BaseDamage_Physical(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, BaseDamage_Physical, OldValue);
}

void UFLCharStatAttributeSet::OnRep_BaseDamage_Ranged(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, BaseDamage_Ranged, OldValue);
}

void UFLCharStatAttributeSet::OnRep_BaseDamage_Magic(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, BaseDamage_Magic, OldValue);
}

void UFLCharStatAttributeSet::OnRep_DamageBonus_Earth(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, DamageBonus_Earth, OldValue);
}

void UFLCharStatAttributeSet::OnRep_DamageBonus_Air(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, DamageBonus_Air, OldValue);
}

void UFLCharStatAttributeSet::OnRep_DamageBonus_Fire(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, DamageBonus_Fire, OldValue);
}

void UFLCharStatAttributeSet::OnRep_DamageBonus_Water(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, DamageBonus_Water, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Defense, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Defense(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Defense, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Resist_Damage(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Resist_Damage, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Resist_Earth(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Resist_Earth, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Resist_Air(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Resist_Air, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Resist_Fire(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Resist_Fire, OldValue);
}

void UFLCharStatAttributeSet::OnRep_Resist_Water(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UFLCharStatAttributeSet, Resist_Water, OldValue);
}