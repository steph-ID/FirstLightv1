// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstLight/FirstLight.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "FirstLightGameTypes.h"
#include "FirstLight/AbilitySystem/Abilities/FLGameplayAbility.h"
#include "FirstLight/ActorComponents/FootstepsComponent.h"
#include "FirstLightCharacter.generated.h"

class AFirstLightPlayerState;
class AFirstLightPlayerController;
class UFLAbilitySystemComponent;
class UFLAttributeSetBase;
class UFLGameplayAbility;

class UGameplayEffect;
class UGameplayAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, AFirstLightCharacter*, Character);

UCLASS(config=Game)
class AFirstLightCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool Crouched = false;

	
public:
	AFirstLightCharacter(const class FObjectInitializer& ObjectInitializer);
	
	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;

	virtual void PostInitializeComponents() override;

	bool ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext) const;

	UPROPERTY(BlueprintAssignable, Category = "First Light|Character")
	FCharacterDiedDelegate OnCharacterDied;

	UFUNCTION(BlueprintCallable, Category = "First Light|Character")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "First Light|Character")
	virtual int32 GetAbilityLevel(EFLAbilityInputID AbilityID) const;

	virtual void RemoveCharacterAbilities();

	UFUNCTION(BlueprintCallable, Category = "First Light|Character")
	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "First Light|Character")
	virtual void FinishDying();

	/*
	// Attribute getters
	UFUNCTION(BlueprintCallable, Category = "First Light|Character|Attributes")
	int32 GetCharacterLevel() const;
	
	UFUNCTION(BlueprintCallable, Category = "First Light|Character|Attributes")
	float GetHealth() const;
	
	UFUNCTION(BlueprintCallable, Category = "First Light|Character|Attributes")
	float GetMaxHealth() const;
	
	UFUNCTION(BlueprintCallable, Category = "First Light|Character|Attributes")
	float GetMana() const;
	
	UFUNCTION(BlueprintCallable, Category = "First Light|Character|Attributes")
	float GetMaxMana() const;
	
	UFUNCTION(BlueprintCallable, Category = "First Light|Character|Attributes")
	float GetStamina() const;
	
	UFUNCTION(BlueprintCallable, Category = "First Light|Character|Attributes")
	float GetMaxStamina() const;*/
	
	// Gets the Current value of MoveSpeed
	/*UFUNCTION(BlueprintCallable, Category = "First Light|GDCharacter|Attributes")
	float GetMoveSpeed() const;*/

protected:
	// Class Overrides
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void OnJumped_Implementation() override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void NotifyJumpApex() override;
	virtual void OnRep_PlayerState() override;

	// Instead of TWeakObjectPtrs, you could just have UPROPERTY() hard references or no references at all and just call
	// GetAbilitySystem() and make a GetAttributeSetBase() that can read from the PlayerState or from child classes.
	// Just make sure you test if the pointer is valid before using.
	// I opted for TWeakObjectPtrs because I didn't want a shared hard reference here and I didn't want an extra function call of getting
	// the ASC/AttributeSet from the PlayerState or child classes every time I referenced them in this base class.

	TWeakObjectPtr<class UFLAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UFLAttributeSetBase> AttributeSetBase;
	
	bool ASCInputBound = false;
	
	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="First Light|Character")
	FText CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="First Light|Animation")
	UAnimMontage* DeathMontage;

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "First Light|Abilities")
	TArray<TSubclassOf<class UFLGameplayAbility>> CharacterAbilities;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "First Light|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "First Light|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	//virtual void AddCharacterAbilities();

	// Initialize the Character's attributes. Must run on Server but we run it on Client too
	// so that we don't have to wait. The Server's replication to the Client won't matter since
	// the values should be the same.
	//virtual void InitializeAttributes();

	//virtual void AddStartupEffects();

	// Called from both SetupPlayerInputComponent and OnRep_PlayerState because of a potential race condition where the PlayerController might
	// call ClientRestart which calls SetupPlayerInputComponent before the PlayerState is repped to the client so the PlayerState would be null in SetupPlayerInputComponent.
	// Conversely, the PlayerState might be repped before the PlayerController calls ClientRestart so the Actor's InputComponent would be null in OnRep_PlayerState.
	void BindASCInput();
	
public:
	// --- Ability System
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void AddStartupGameplayAbilities();
	void ApplyStartupEffects();
	
	UFUNCTION(BlueprintCallable, Category = "First Light|Character")
	AFirstLightPlayerController* GetFirstLightPlayerController() const;
	
	UFUNCTION(BlueprintCallable, Category = "First Light|Character")
	AFirstLightPlayerState* GetFLPlayerState() const;
	
	UFUNCTION(BlueprintCallable, Category = "First Light|Character")
	UFLAbilitySystemComponent* GetFLAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="First Light|Abilities")
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="First Light|Abilities")
	TArray<TSubclassOf<UFLGameplayAbility>> GameplayAbilities;

	UPROPERTY()
	uint8 bAbilitiesInitialized:1;

	/**
	 * Called when character takes damage, which may have killed them
	 *
	 * @param DamageAmount Amount of damage that was done, not clamped based on current health
	 * @param HitInfo The hit info that generated this damage
	 * @param DamageTags The gameplay tags of the event that did the damage
	 * @param InstigatorCharacter The character that initiated this damage
	 * @param DamageCauser The actual actor that did the damage, might be a weapon or projectile
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnDamaged(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, AFirstLightCharacter* InstigatorCharacter, AActor* DamageCauser);

	/**
	 * Called when health is changed, either from healing or from being damaged
	 * For damage this is called in addition to OnDamaged/OnKilled
	 *
	 * @param DeltaValue Change in health value, positive for heal, negative for cost. If 0 the delta is unknown
	 * @param EventTags The gameplay tags of the event that changed mana
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	
public:
	virtual void HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, AFirstLightCharacter* InstigatorCharacter, AActor* DamageCauser);
	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	// Components
	UFootstepsComponent* GetFootstepsComponent() const;
	
protected:

	UPROPERTY(BlueprintReadOnly, Category="First Light")
	class UFootstepsComponent* FootstepsComponent;
	
	/*UPROPERTY(EditDefaultsOnly, Category="First Light|Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;*/
	
	//UPROPERTY(Transient)
	//UFLAttributeSetBase* AttributeSet;
	
	// Attribute Setters
/*	virtual void SetHealth(float Health);
	virtual void SetMana(float Mana);
	virtual void SetStamina(float Stamina);*/
	//virtual void SetCharacterLevel(int32 LevelCount);

public:
	/** Returns CameraBoom sub object **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera sub object **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	FCharacterData GetCharacterData() const;

	UFUNCTION(BlueprintCallable)
	void SetCharacterData(const FCharacterData& InCharacterData);

protected:
	
	UPROPERTY(ReplicatedUsing = OnRep_CharacterData)
	FCharacterData CharacterData;

	UFUNCTION()
	void OnRep_CharacterData();
	
	virtual void InitFromCharacterData(const FCharacterData& InCharacterData, bool bFromReplication = false);

	UPROPERTY(EditDefaultsOnly, Category = "First Light")
	class UCharacterDataAsset* CharacterDataAsset;

public:
	// --- ABILITY TAGS
	
	UPROPERTY(EditDefaultsOnly, Category = "First Light|Tags")
	FGameplayTagContainer InAirTags;
	
	UPROPERTY(EditDefaultsOnly, Category = "First Light|Tags")
	FGameplayTagContainer SprintTags;
	
	UPROPERTY(EditDefaultsOnly, Category = "First Light|Tags")
	FGameplayTagContainer CombatTags;
	
	UPROPERTY(EditDefaultsOnly, Category = "First Light|Tags")
	FGameplayTag JumpEventTag;

protected:

	FDelegateHandle MaxMovementSpeedChangedDelegateHandle;

public:
	void OnMaxMovementSpeedChanged(const FOnAttributeChangeData& Data);
};