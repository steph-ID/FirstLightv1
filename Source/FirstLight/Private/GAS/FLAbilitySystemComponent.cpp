// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/FLAbilitySystemComponent.h"

void UFLAbilitySystemComponent::ReceiveDamage(UFLAbilitySystemComponent* SourceAsc,
	float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.Broadcast(SourceAsc, UnmitigatedDamage, MitigatedDamage);
}