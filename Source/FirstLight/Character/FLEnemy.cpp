// Fill out your copyright notice in the Description page of Project Settings.


#include "FLEnemy.h"

#include "FirstLight/FirstLight.h"
#include "FirstLight/AbilitySystem/FLAbilitySystemComponent.h"
#include "FirstLight/AbilitySystem/FLAttributeSetBase.h"

AFLEnemy::AFLEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UFLAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UFLAttributeSetBase>("AttributeSet");

	/*HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());*/
}

void AFLEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AFLEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
}

int32 AFLEnemy::GetPlayerLevel()
{
	return Level;
}

void AFLEnemy::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitAbilityActorInfo();

	/* if (UFLUserWidget* FLUserWidget = Cast<UFLUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		FLUserWidget->SetWidgetController(this);
	}

	if (const UFLAttributeSetBase* FLAS = Cast<UFLAttributeSetBase>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FLAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
			);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FLAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
			);
		
		OnHealthChanged.Broadcast(FLAS->GetHealth());
		OnMaxHealthChanged.Broadcast(FLAS->GetMaxHealth());
	}*/
}

void AFLEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UFLAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	//InitializeDefaultAttributes();
}