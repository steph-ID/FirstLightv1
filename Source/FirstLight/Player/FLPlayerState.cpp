// Fill out your copyright notice in the Description page of Project Settings.


#include "FLPlayerState.h"
#include "FirstLight/AbilitySystem/FLAbilitySystemComponent.h"
//#include "FirstLight/AbilitySystem/FLAttributeSet.h"
#include "FirstLight/AbilitySystem/FLCharStatAttributeSet.h"
#include "Net/UnrealNetwork.h"

AFLPlayerState::AFLPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UFLAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UFLCharStatAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void AFLPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AFLPlayerState, Level);
}

UAbilitySystemComponent* AFLPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AFLPlayerState::OnRep_Level(int32 OldLevel)
{
}
