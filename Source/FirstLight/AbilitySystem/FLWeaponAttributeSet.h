// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "FLWeaponAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API UFLWeaponAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UFLWeaponAttributeSet();
	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet|Item")
	FGameplayAttributeData ItemLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet|Item")
	FGameplayAttributeData RequiredLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet|Item")
	FGameplayAttributeData Slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet|Item")
	FGameplayAttributeData BasePrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet|Item")
	FGameplayAttributeData ItemPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet|Item")
	FGameplayAttributeData BaseDropRate;

	protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};