// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstLightCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FirstLight/FirstLightPlayerController.h"
// GAS includes
#include "AbilitySystemComponent.h"
#include "FirstLight/AbilitySystem/Abilities/FLGameplayAbility.h"
#include "FirstLight/ActorComponents/FLCharacterMovementComponent.h"
#include "FirstLight/ActorComponents/FootstepsComponent.h"
#include "FirstLightPlayerState.h"
#include "FirstLight/DataAssets/CharacterDataAsset.h"
#include "GAS/FLAttributeSetBase.h"
#include "GAS/FLAbilitySystemComponent.h"

#include "Net/UnrealNetwork.h"

//////////////////////////////////////////////////////////////////////////
// AFirstLightCharacter

AFirstLightCharacter::AFirstLightCharacter(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UFLCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	FootstepsComponent = CreateDefaultSubobject<UFootstepsComponent>(TEXT("FootstepsComponent"));

	// Gameplay Ability System
	bAbilitiesInitialized = false;
	
	//AbilitySystemComponent = CreateDefaultSubobject<UFLAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	//AbilitySystemComponent->SetIsReplicated(true);
	//AbilitySystemComponent->SetReplicationMode((EGameplayEffectReplicationMode::Mixed));
	
	//const AFirstLightPlayerState* FLPlayerState = GetPlayerState<AFirstLightPlayerState>();
	//AbilitySystemComponent = GetFLPlayerState()->GetFLAbilitySystemComponent();
	
	//AttributeSet = CreateDefaultSubobject<UFLAttributeSetBase>(TEXT("AttributeSet"));

	//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxMovementSpeedAttribute()).AddUObject(this, &AFirstLightCharacter::OnMaxMovementSpeedChanged);
	
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

UAbilitySystemComponent * AFirstLightCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

bool AFirstLightCharacter::IsAlive() const
{
	return GetFLPlayerState()->GetAttributeSetBase()->GetHealth() > 0.0f;
}

int32 AFirstLightCharacter::GetAbilityLevel(EFLAbilityInputID AbilityID) const
{
	return 1;
}

void AFirstLightCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<AFirstLightPlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

AFirstLightPlayerController* AFirstLightCharacter::GetFirstLightPlayerController() const
{
	return CastChecked<AFirstLightPlayerController>(Controller, ECastCheckedType::NullAllowed);
}

AFirstLightPlayerState* AFirstLightCharacter::GetFLPlayerState() const
{
	return CastChecked<AFirstLightPlayerState>(GetPlayerState(), ECastCheckedType::NullAllowed);
}

UFLAbilitySystemComponent* AFirstLightCharacter::GetFLAbilitySystemComponent() const
{
	return Cast<UFLAbilitySystemComponent>(GetAbilitySystemComponent());
}

/*UAbilitySystemComponent* AFirstLightCharacter::GetAbilitySystemComponent() const
{
	//return PawnExtComponent->GetFLAbilitySystemComponent();
	//GetFLPlayerState()->
	return GetFLPlayerState()->GetFLAbilitySystemComponent();
}*/

//////////////////////////////////////////////////////////////////////////
// Input

void AFirstLightCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (AbilitySystemComponent.IsValid() && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds(
			"Confirm",
			"Cancel",
			"EFirstLightAbilityInputID",
			static_cast<int32>(EFLAbilityInputID::Confirm),
			static_cast<int32>(EFLAbilityInputID::Cancel));
		
		//AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

void AFirstLightCharacter::RemoveCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || !AbilitySystemComponent->bCharacterAbilitiesGiven)
	{
		return;
	}

	// Remove any abilities added from a previous call. This checks to make sure the ability is in the startup 'CharacterAbilities' array.
	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	// Do in two passes so the removal happens after we have the full list
	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
	{
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}

	AbilitySystemComponent->bCharacterAbilitiesGiven = false;
}

//--- Death
void AFirstLightCharacter::Die()
{
	// Only runs on Server
	RemoveCharacterAbilities();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//GetCharacterMovement()->GravityScale = 0;
	//GetCharacterMovement()->Velocity = FVector(0);

	OnCharacterDied.Broadcast(this);

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->CancelAllAbilities();

		FGameplayTagContainer EffectTagsToRemove;
		EffectTagsToRemove.AddTag(EffectRemoveOnDeathTag);
		int32 NumEffectsRemoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectTagsToRemove);

		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}

	if (DeathMontage)
	{
		//PlayAnimMontage(DeathMontage);
	}
	else
	{
		FinishDying();
	}
}
void AFirstLightCharacter::FinishDying()
{
	//Destroy();
}

UFootstepsComponent* AFirstLightCharacter::GetFootstepsComponent() const
{
	return FootstepsComponent;
}

//--- Ability System
void AFirstLightCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AFirstLightPlayerState* FLPlayerState = GetPlayerState<AFirstLightPlayerState>();
	if (FLPlayerState)
	{
		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
		AbilitySystemComponent = Cast<UFLAbilitySystemComponent>(FLPlayerState->GetAbilitySystemComponent());

		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in initing twice for heroes that have PlayerControllers.
		FLPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(FLPlayerState, this);

		// Set the AttributeSetBase for convenience attribute functions
		AttributeSetBase = FLPlayerState->GetAttributeSetBase();

		// If we handle players disconnecting and rejoining in the future, we'll have to change this so that possession from rejoining doesn't reset attributes.
		// For now assume possession = spawn/respawn.
		//InitializeAttributes();

		
		// Respawn specific things that won't affect first possession.

		// Forcibly set the DeadTag count to 0
		AbilitySystemComponent->SetTagMapCount(DeadTag, 0);

		// Set Health/Mana/Stamina to their max. This is only necessary for *Respawn*.
		//SetHealth(GetMaxHealth());
		//SetMana(GetMaxMana());
		//SetStamina(GetMaxStamina());

		// End respawn specific things


		ApplyStartupEffects();
		AddStartupGameplayAbilities();
		
		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
		//UFLAbilitySystemComponent* AbilitySystemComponent = Cast<UFLAbilitySystemComponent>(FLPlayerState->GetFLAbilitySystemComponent());

		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in initing twice for heroes that have PlayerControllers.
		//AbilitySystemComponent->InitAbilityActorInfo(FLPlayerState, this);
	}
}
void AFirstLightCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	AFirstLightPlayerState* FLPlayerState = GetPlayerState<AFirstLightPlayerState>();
	if (FLPlayerState)
	{
		// Set the ASC for clients. Server does this in PossessedBy.
		AbilitySystemComponent = Cast<UFLAbilitySystemComponent>(FLPlayerState->GetAbilitySystemComponent());

		// Init ASC Actor Info for clients. Server will init its ASC when it possesses a new Actor.
		AbilitySystemComponent->InitAbilityActorInfo(FLPlayerState, this);

		// Bind player input to the AbilitySystemComponent. Also called in SetupPlayerInputComponent because of a potential race condition.
		//BindASCInput();

		// Set the AttributeSetBase for convenience attribute functions
		AttributeSetBase = FLPlayerState->GetAttributeSetBase();

		// If we handle players disconnecting and rejoining in the future, we'll have to change this so that posession from rejoining doesn't reset attributes.
		// For now assume possession = spawn/respawn.
		//InitializeAttributes();
		
		// Forcibly set the DeadTag count to 0
		AbilitySystemComponent->SetTagMapCount(DeadTag, 0);
		
		//SetHealth(GetMaxHealth());
		//SetMana(GetMaxMana());
		//SetStamina(GetMaxStamina());
		
		// Set the ASC for clients. Server does this in PossessedBy.
		//UFLAbilitySystemComponent* AbilitySystemComponent = Cast<UFLAbilitySystemComponent>(FLPlayerState->GetAbilitySystemComponent());

		// Init ASC Actor Info for clients. Server will init its ASC when it possesses a new Actor.
		//AbilitySystemComponent->InitAbilityActorInfo(FLPlayerState, this);
	}

	if (AbilitySystemComponent.IsValid() && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds(
			"Confirm",
			"Cancel",
			"EFirstLightAbilityInputID",
			static_cast<int32>(EFLAbilityInputID::Confirm),
			static_cast<int32>(EFLAbilityInputID::Cancel));
		
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

void AFirstLightCharacter::BindASCInput()
{
/*	if (!ASCInputBound && AbilitySystemComponent.IsValid() && IsValid(InputComponent))
	{
		FTopLevelAssetPath AbilityEnumAssetPath = FTopLevelAssetPath(FName("/Script/GASDocumentation"), FName("EGDAbilityInputID"));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"),
			FString("CancelTarget"), AbilityEnumAssetPath, static_cast<int32>(EGDAbilityInputID::Confirm), static_cast<int32>(EGDAbilityInputID::Cancel)));

		ASCInputBound = true;
	}*/
}

void AFirstLightCharacter::ApplyStartupEffects()
{
	// Can run on Server and Client
	if (GetLocalRole() == ROLE_Authority)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		for (auto CharacterEffect : CharacterData.Effects)
		{
			ApplyGameplayEffectToSelf(CharacterEffect, EffectContext);
		}
	}
}
bool AFirstLightCharacter::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext) const
{
	if(!Effect.Get()) return false;
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, InEffectContext);
	
	if (SpecHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		return ActiveGEHandle.WasSuccessfullyApplied();
	}
	return false;
}
void AFirstLightCharacter::AddStartupGameplayAbilities()
{
	//check(AbilitySystemComponent);
	
	// Grant abilities, but only on the server
	if (HasAuthority() && !bAbilitiesInitialized)
	{
		for (TSubclassOf<UFLGameplayAbility> DefaultAbility : CharacterData.Abilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
				DefaultAbility, 1,
				static_cast<int32>(DefaultAbility.GetDefaultObject()->AbilityInputID),
				this));
		}

		// Now apply passives
		for (const TSubclassOf<UGameplayEffect>& GameplayEffect : PassiveGameplayEffects)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(
				GameplayEffect, 1, EffectContext);

			if (NewHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
					*NewHandle.Data.Get(), GetFLPlayerState()->GetFLAbilitySystemComponent());
			}
		}
		
		bAbilitiesInitialized = true;
	}
}
void AFirstLightCharacter::HandleDamage(float DamageAmount, const FHitResult& HitInfo,
	const FGameplayTagContainer& DamageTags, AFirstLightCharacter* InstigatorCharacter, AActor* DamageCauser)
{
	OnDamaged(DamageAmount, HitInfo, DamageTags, InstigatorCharacter, DamageCauser);
}
void AFirstLightCharacter::HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	if (bAbilitiesInitialized)
	{
		OnHealthChanged(DeltaValue, EventTags);
		if (GetFLPlayerState()->GetHealth() <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Adding DeadTag"))
			AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
		}
	}
}
/*
//--- Attribute Setters
void AFirstLightCharacter::SetCharacterLevel(int32 LevelCount)
{
}
void AFirstLightCharacter::SetHealth(float Health)
{
	if (IsValid(AttributeSet))
	{
		AttributeSet->SetHealth(Health);
	}
}
void AFirstLightCharacter::SetMana(float Mana)
{
	if (IsValid(AttributeSet))
	{
		AttributeSet->SetMana(Mana);
	}
}
void AFirstLightCharacter::SetStamina(float Stamina)
{
	if (IsValid(AttributeSet))
	{
		AttributeSet->SetStamina(Stamina);
	}
}*/

void AFirstLightCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(IsValid(CharacterDataAsset))
	{
		SetCharacterData(CharacterDataAsset->CharacterData);
	}
}

FCharacterData AFirstLightCharacter::GetCharacterData() const
{
	return CharacterData;
}

void AFirstLightCharacter::SetCharacterData(const FCharacterData& InCharacterData)
{
	CharacterData = InCharacterData;

	InitFromCharacterData(CharacterData);
}

void AFirstLightCharacter::InitFromCharacterData(const FCharacterData& InCharacterData, bool bFromReplication)
{
	
}

void AFirstLightCharacter::OnRep_CharacterData()
{
	InitFromCharacterData(CharacterData, true);
}

void AFirstLightCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFirstLightCharacter, CharacterData);
}

//--- Jumping
void AFirstLightCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->RemoveActiveEffectsWithTags(InAirTags);
	}
}
void AFirstLightCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
}
void AFirstLightCharacter::NotifyJumpApex()
{
	Super::NotifyJumpApex();
}

void AFirstLightCharacter::OnMaxMovementSpeedChanged(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
}
