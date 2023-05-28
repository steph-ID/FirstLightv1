// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTLIGHT_API UItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemComponent();

private:
	/*int ItemLevel;
	float ItemPrice;
	float ItemAttribute;*/

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Setters
	int SetItemLevel(float BaseItemLevel, int ItemLevelMultiplier);
	float SetItemPrice(float BaseItemPrice, int RarityMultiplier);
	float SetItemAttribute(float BaseItemAttribute, int RarityMultiplier);

	// Getters
	int GetItemLevel();
	float GetItemPrice();
	float GetItemAttribute();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
