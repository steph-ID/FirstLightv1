// Fill out your copyright notice in the Description page of Project Settings.


#include "FLCharacterBase.h"
#include "AbilitySystemComponent.h"

// Sets default values
AFLCharacterBase::AFLCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

UAbilitySystemComponent* AFLCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AFLCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFLCharacterBase::InitAbilityActorInfo()
{
}

void AFLCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}
void AFLCharacterBase::InitializePrimaryAttributes() const
{
	for (const TSubclassOf<UGameplayEffect> DefaultAttributeSet : DefaultAttributes)
	{
		//ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
		ApplyEffectToSelf(DefaultAttributeSet, 1.f);
	}
}
