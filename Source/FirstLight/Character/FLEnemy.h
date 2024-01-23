// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FLCharacterBase.h"
#include "FirstLight/Interaction/CombatInterface.h"
#include "FirstLight/Interaction/EnemyInterface.h"
#include "FLEnemy.generated.h"

class UWidgetComponent;

/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API AFLEnemy : public AFLCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AFLEnemy();

	/** Enemy Interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** End Enemy Interface */
	
	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** End Combat Interface */

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

	/** Enemy Health Widget 
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;*/

protected:

	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
	
};
