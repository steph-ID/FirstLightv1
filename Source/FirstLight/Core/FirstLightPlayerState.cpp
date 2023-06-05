// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstLightPlayerState.h"

#include "FirstLightPlayerCharacter.h"
#include "FirstLight/FirstLightPlayerController.h"
#include "FirstLight/AbilitySystem/FLAbilitySystemComponent.h"
#include "FirstLight/Widgets/FirstLightGameWidget.h"
#include "FirstLight/Widgets/FLFloatingStatusBarWidget.h"

AFirstLightPlayerState::AFirstLightPlayerState()
{
	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UFLAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// Mixed mode means we only are replicated the GEs to ourself, not the GEs to simulated proxies. If another GDPlayerState (Character) receives a GE,
	// we won't be told about it by the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// Create the attribute set, this replicates by default
	// Adding it as a subobject of the owning actor of an AbilitySystemComponent
	// automatically registers the AttributeSet with the AbilitySystemComponent
	AttributeSetBase = CreateDefaultSubobject<UFLAttributeSetBase>(TEXT("AttributeSetBase"));

	// Set PlayerState's NetUpdateFrequency to the same as the Character.
	// Default is very low for PlayerStates and introduces perceived lag in the ability system.
	// 100 is probably way too high for a shipping game, you can adjust to fit your needs.
	NetUpdateFrequency = 100.0f;

	// Cache tags
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

UAbilitySystemComponent* AFirstLightPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UFLAttributeSetBase* AFirstLightPlayerState::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

void AFirstLightPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		// Attribute change callbacks
		CharacterLevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetCharacterLevelAttribute()).AddUObject(this, &AFirstLightPlayerState::CharacterLevelChanged);
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &AFirstLightPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &AFirstLightPlayerState::MaxHealthChanged);
		HealthRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthRegenRateAttribute()).AddUObject(this, &AFirstLightPlayerState::HealthRegenRateChanged);
		ManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetManaAttribute()).AddUObject(this, &AFirstLightPlayerState::ManaChanged);
		MaxManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxManaAttribute()).AddUObject(this, &AFirstLightPlayerState::MaxManaChanged);
		ManaRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetManaRegenRateAttribute()).AddUObject(this, &AFirstLightPlayerState::ManaRegenRateChanged);
		StaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetStaminaAttribute()).AddUObject(this, &AFirstLightPlayerState::StaminaChanged);
		MaxStaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxStaminaAttribute()).AddUObject(this, &AFirstLightPlayerState::MaxStaminaChanged);
		StaminaRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetStaminaRegenRateAttribute()).AddUObject(this, &AFirstLightPlayerState::StaminaRegenRateChanged);
		XPChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetXPAttribute()).AddUObject(this, &AFirstLightPlayerState::XPChanged);
		GoldChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetGoldAttribute()).AddUObject(this, &AFirstLightPlayerState::GoldChanged);
		ArenaLevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetArenaLevelAttribute()).AddUObject(this, &AFirstLightPlayerState::ArenaLevelChanged);
		ArenaXPChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetArenaXPAttribute()).AddUObject(this, &AFirstLightPlayerState::ArenaXPChanged);
		ArenaMaxXPChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetArenaMaxXPAttribute()).AddUObject(this, &AFirstLightPlayerState::ArenaMaxXPChanged);
		ArenaScoreChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetArenaScoreAttribute()).AddUObject(this, &AFirstLightPlayerState::ArenaScoreChanged);
		ArenaTopScoreChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetArenaTopScoreAttribute()).AddUObject(this, &AFirstLightPlayerState::ArenaTopScoreChanged);
		ArenaKillsChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetArenaKillsAttribute()).AddUObject(this, &AFirstLightPlayerState::ArenaKillsChanged);
		ArenaDeathsChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetArenaDeathsAttribute()).AddUObject(this, &AFirstLightPlayerState::ArenaDeathsChanged);
		ArenaAssistsChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetArenaAssistsAttribute()).AddUObject(this, &AFirstLightPlayerState::ArenaAssistsChanged);

		// Tag change callbacks
		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AFirstLightPlayerState::StunTagChanged);
	}
}

AFirstLightPlayerController* AFirstLightPlayerState::GetFirstLightPlayerController() const
{
	return Cast<AFirstLightPlayerController>(GetOwner());
}

bool AFirstLightPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

int32 AFirstLightPlayerState::GetCharacterLevel() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetCharacterLevel();
	}
	return 1; // Default level
}

int32 AFirstLightPlayerState::GetXP() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetXP();
	}
	return 0;
}

int32 AFirstLightPlayerState::GetMaxXP() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetMaxXP();
	}
	return 0;
}

float AFirstLightPlayerState::GetHealth() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetHealth();
	}
	return 0.0f;
}

float AFirstLightPlayerState::GetMaxHealth() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetMaxHealth();
	}
	return 0.0f;
}

float AFirstLightPlayerState::GetHealthRegenRate() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetHealthRegenRate();
	}
	return 0.0f;
}

float AFirstLightPlayerState::GetMana() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetMana();
	}
	return 0.0f;
}

float AFirstLightPlayerState::GetMaxMana() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetMaxMana();
	}
	return 0.0f;
}

float AFirstLightPlayerState::GetManaRegenRate() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetManaRegenRate();
	}
	return 0.0f;
}

float AFirstLightPlayerState::GetStamina() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetStamina();
	}
	return 0.0f;
}

float AFirstLightPlayerState::GetMaxStamina() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetMaxStamina();
	}
	return 0.0f;
}

float AFirstLightPlayerState::GetStaminaRegenRate() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetStaminaRegenRate();
	}
	return 0.0f;
}

float AFirstLightPlayerState::GetArmor() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetArmor();
	}
	return 0.0f;
}

float AFirstLightPlayerState::GetMovementSpeed() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetMovementSpeed();
	}
	return 0.0f;
}

float AFirstLightPlayerState::GetMaxMovementSpeed() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetMaxMovementSpeed();
	}
	return 0.0f;
}

int32 AFirstLightPlayerState::GetGold() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetGold();
	}
	return 0;
}

int32 AFirstLightPlayerState::GetArenaLevel() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetArenaLevel();
	}
	return 1; // Default level
}

int32 AFirstLightPlayerState::GetArenaXP() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetArenaXP();
	}
	return 0;
}

int32 AFirstLightPlayerState::GetArenaMaxXP() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetArenaMaxXP();
	}
	return 0;
}

int32 AFirstLightPlayerState::GetArenaScore() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetArenaScore();
	}
	return 0;
}

int32 AFirstLightPlayerState::GetArenaTopScore() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetArenaTopScore();
	}
	return 0;
}

int32 AFirstLightPlayerState::GetArenaKills() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetArenaKills();
	}
	return 0;
}

int32 AFirstLightPlayerState::GetArenaDeaths() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetArenaDeaths();
	}
	return 0;
}

int32 AFirstLightPlayerState::GetArenaAssists() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetArenaAssists();
	}
	return 0;
}

void AFirstLightPlayerState::CharacterLevelChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::XPChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::MaxXPChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;

	// Update floating status bar
	AFirstLightPlayerCharacter* Character = Cast<AFirstLightPlayerCharacter>(GetPawn());
	if (Character)
	{
		UFLFloatingStatusBarWidget* PlayerFloatingStatusBar = Character->GetFloatingStatusBar();
		if (PlayerFloatingStatusBar)
		{
			PlayerFloatingStatusBar->SetHealthPercentage(Health / GetMaxHealth());
		}
	}

	// Update the HUD
	// Handled in the UI itself using the AsyncTaskAttributeChanged node as an example how to do it in Blueprint

	// If the player died, handle death
	if (!IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
		if (Character)
		{
			Character->Die();
		}
	}
}

void AFirstLightPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	float MaxHealth = Data.NewValue;

	// Update floating status bar
	AFirstLightPlayerCharacter* Character = Cast<AFirstLightPlayerCharacter>(GetPawn());
	if (Character)
	{
		UFLFloatingStatusBarWidget* PlayerFloatingStatusBar = Character->GetFloatingStatusBar();
		if (PlayerFloatingStatusBar)
		{
			PlayerFloatingStatusBar->SetHealthPercentage(GetHealth() / MaxHealth);
		}
	}

	// Update the HUD
	AFirstLightPlayerController* PC = Cast<AFirstLightPlayerController>(GetOwner());
	if (PC)
	{
		UFirstLightGameWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetMaxHealth(MaxHealth);
		}
	}
}

void AFirstLightPlayerState::HealthRegenRateChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::ManaChanged(const FOnAttributeChangeData& Data)
{
	float Mana = Data.NewValue;

	// Update floating status bar
	AFirstLightPlayerCharacter* Character = Cast<AFirstLightPlayerCharacter>(GetPawn());
	if (Character)
	{
		UFLFloatingStatusBarWidget* PlayerFloatingStatusBar = Character->GetFloatingStatusBar();
		if (PlayerFloatingStatusBar)
		{
			PlayerFloatingStatusBar->SetManaPercentage(Mana / GetMaxMana());
		}
	}

	// Update the HUD
	// Handled in the UI itself using the AsyncTaskAttributeChanged node as an example how to do it in Blueprint
}

void AFirstLightPlayerState::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	float MaxMana = Data.NewValue;

	// Update floating status bar
	AFirstLightPlayerCharacter* Character = Cast<AFirstLightPlayerCharacter>(GetPawn());
	if (Character)
	{
		UFLFloatingStatusBarWidget* PlayerFloatingStatusBar = Character->GetFloatingStatusBar();
		if (PlayerFloatingStatusBar)
		{
			PlayerFloatingStatusBar->SetManaPercentage(GetMana() / MaxMana);
		}
	}

	// Update the HUD
	AFirstLightPlayerController* PC = Cast<AFirstLightPlayerController>(GetOwner());
	if (PC)
	{
		UFirstLightGameWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetMaxMana(MaxMana);
		}
	}
}

void AFirstLightPlayerState::ManaRegenRateChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::StaminaChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::MaxStaminaChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::StaminaRegenRateChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::MovementSpeedChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::MaxMovementSpeedChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::ArmorChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::GoldChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::ArenaLevelChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::ArenaXPChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::ArenaMaxXPChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::ArenaScoreChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::ArenaTopScoreChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::ArenaKillsChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::ArenaDeathsChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::ArenaAssistsChanged(const FOnAttributeChangeData& Data)
{
}

void AFirstLightPlayerState::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCanceledByStun")));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}
}

void AFirstLightPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	AFirstLightPlayerController* PC = Cast<AFirstLightPlayerController>(GetOwner());
	if (PC)
	{
		UFirstLightGameWidget* PlayerHUD = PC->GetHUD();
		if (PlayerHUD)
		{
			PlayerHUD->ShowAbilityConfirmCancelText(ShowText);
		}
	}
}
