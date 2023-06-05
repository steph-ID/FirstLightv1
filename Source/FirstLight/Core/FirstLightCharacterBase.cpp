// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstLightCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "FirstLight/AbilitySystem/Abilities/FLGameplayAbility.h"
#include "FirstLight/ActorComponents/FLCharacterMovementComponent.h"
#include "FirstLight/DataAssets/CharacterDataAsset.h"
#include "FirstLight/AbilitySystem/FLAbilitySystemComponent.h"
#include "FirstLight/AbilitySystem/FLAttributeSetBase.h"
#include "FirstLight/AbilitySystem/Abilities/GA_Jump.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AFirstLightCharacterBase::AFirstLightCharacterBase(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UFLCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);

	bAlwaysRelevant = true;

	// Cache tags
	HitDirectionFrontTag = FGameplayTag::RequestGameplayTag(FName("Effect.HitReact.Front"));
	HitDirectionBackTag = FGameplayTag::RequestGameplayTag(FName("Effect.HitReact.Back"));
	HitDirectionRightTag = FGameplayTag::RequestGameplayTag(FName("Effect.HitReact.Right"));
	HitDirectionLeftTag = FGameplayTag::RequestGameplayTag(FName("Effect.HitReact.Left"));
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("Effect.RemoveOnDeath"));
	
	/*TSubclassOf<UFLAttributeSetBase> UFLAttributeSetBase* 
    const TSubclassOf<UFLAttributeSetBase> AttributeSet = UFLAttributeSetBase::StaticClass();
	AttributeSetBase = AttributeSet.Get();*/
	
}

UAbilitySystemComponent * AFirstLightCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

bool AFirstLightCharacterBase::IsAlive() const
{
	return GetHealth() > 0.0f;
}

int32 AFirstLightCharacterBase::GetAbilityLevel(EFLAbilityInputID AbilityID) const
{
	return 1;
}

void AFirstLightCharacterBase::RemoveCharacterAbilities()
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

EFLHitReactDirection AFirstLightCharacterBase::GetHitReactDirection(const FVector & ImpactPoint)
{
	const FVector& ActorLocation = GetActorLocation();
	// PointPlaneDist is super cheap - 1 vector subtraction, 1 dot product.
	float DistanceToFrontBackPlane = FVector::PointPlaneDist(ImpactPoint, ActorLocation, GetActorRightVector());
	float DistanceToRightLeftPlane = FVector::PointPlaneDist(ImpactPoint, ActorLocation, GetActorForwardVector());


	if (FMath::Abs(DistanceToFrontBackPlane) <= FMath::Abs(DistanceToRightLeftPlane))
	{
		// Determine if Front or Back

		// Can see if it's left or right of Left/Right plane which would determine Front or Back
		if (DistanceToRightLeftPlane >= 0)
		{
			return EFLHitReactDirection::Front;
		}
		else
		{
			return EFLHitReactDirection::Back;
		}
	}
	else
	{
		// Determine if Right or Left

		if (DistanceToFrontBackPlane >= 0)
		{
			return EFLHitReactDirection::Right;
		}
		else
		{
			return EFLHitReactDirection::Left;
		}
	}

	return EFLHitReactDirection::Front;
}

void AFirstLightCharacterBase::PlayHitReact_Implementation(FGameplayTag HitDirection, AActor * DamageCauser)
{
	if (IsAlive())
	{
		if (HitDirection == HitDirectionLeftTag)
		{
			ShowHitReact.Broadcast(EFLHitReactDirection::Left);
		}
		else if (HitDirection == HitDirectionFrontTag)
		{
			ShowHitReact.Broadcast(EFLHitReactDirection::Front);
		}
		else if (HitDirection == HitDirectionRightTag)
		{
			ShowHitReact.Broadcast(EFLHitReactDirection::Right);
		}
		else if (HitDirection == HitDirectionBackTag)
		{
			ShowHitReact.Broadcast(EFLHitReactDirection::Back);
		}
	}
}

bool AFirstLightCharacterBase::PlayHitReact_Validate(FGameplayTag HitDirection, AActor * DamageCauser)
{
	return true;
}

int32 AFirstLightCharacterBase::GetCharacterLevel() const
{
	if (AttributeSetBase.IsValid())
	{
		return static_cast<int32>(AttributeSetBase->GetCharacterLevel());
	}

	return 0;
}

float AFirstLightCharacterBase::GetHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetHealth();
	}

	return 0.0f;
}

float AFirstLightCharacterBase::GetMaxHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxHealth();
	}

	return 0.0f;
}

float AFirstLightCharacterBase::GetMana() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMana();
	}

	return 0.0f;
}

float AFirstLightCharacterBase::GetMaxMana() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxMana();
	}

	return 0.0f;
}

float AFirstLightCharacterBase::GetStamina() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetStamina();
	}

	return 0.0f;
}

float AFirstLightCharacterBase::GetMaxStamina() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxStamina();
	}

	return 0.0f;
}

float AFirstLightCharacterBase::GetMoveSpeed() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMovementSpeed();
	}

	return 0.0f;
}

float AFirstLightCharacterBase::GetMoveSpeedBaseValue() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMovementSpeedAttribute().GetGameplayAttributeData(AttributeSetBase.Get())->GetBaseValue();
	}

	return 0.0f;
}

// Run on Server and all clients
void AFirstLightCharacterBase::Die()
{
	// Only runs on Server
	RemoveCharacterAbilities();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);

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
		PlayAnimMontage(DeathMontage);
	}
	else
	{
		FinishDying();
	}
}

void AFirstLightCharacterBase::FinishDying()
{
	Destroy();
}

// Called when the game starts or when spawned
void AFirstLightCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AFirstLightCharacterBase::AddCharacterAbilities()
{
	// Grant abilities, but only on the server	
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->bCharacterAbilitiesGiven)
	{
		return;
	}

	for (TSubclassOf<UFLGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	}

	AbilitySystemComponent->bCharacterAbilitiesGiven = true;
}

void AFirstLightCharacterBase::InitializeAttributes()
{
	if (!AbilitySystemComponent.IsValid())
	{
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	if (IsValid(CharacterDataAsset))
	{
		SetCharacterData(CharacterDataAsset->CharacterData);
	}

	// Can run on Server and Client
	/*FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, GetCharacterLevel(), EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}*/
}

void AFirstLightCharacterBase::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->bStartupEffectsApplied)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
	}

	AbilitySystemComponent->bStartupEffectsApplied = true;
}

void AFirstLightCharacterBase::SetHealth(float Health)
{
	if (AttributeSetBase.IsValid())
	{
		AttributeSetBase->SetHealth(Health);
	}
}

void AFirstLightCharacterBase::SetMana(float Mana)
{
	if (AttributeSetBase.IsValid())
	{
		AttributeSetBase->SetMana(Mana);
	}
}

void AFirstLightCharacterBase::SetStamina(float Stamina)
{
	if (AttributeSetBase.IsValid())
	{
		AttributeSetBase->SetStamina(Stamina);
	}
}

/*
 * Character Data Code
*/

bool AFirstLightCharacterBase::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext) const
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

void AFirstLightCharacterBase::ApplyStartupGameplayEffects()
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
		AbilitySystemComponent->bStartupEffectsApplied = true;
	}
}

void AFirstLightCharacterBase::AddStartupGameplayAbilities()
{
	//check(AbilitySystemComponent);
	
	// Grant abilities, but only on the server
	if (HasAuthority() && !AbilitySystemComponent->bCharacterAbilitiesGiven)
	{
		/*for (TSubclassOf<UFLGameplayAbility> DefaultAbility : CharacterData.Abilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
				DefaultAbility, 1,
				static_cast<int32>(DefaultAbility.GetDefaultObject()->AbilityInputID),
				this));
		}*/
		for (auto DefaultAbility : CharacterData.Abilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(DefaultAbility));
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
					*NewHandle.Data.Get(), GetAbilitySystemComponent());
			}
		}
		
		AbilitySystemComponent->bCharacterAbilitiesGiven = true;
	}
}

void AFirstLightCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(IsValid(CharacterDataAsset))
	{
		SetCharacterData(CharacterDataAsset->CharacterData);
	}
}

FCharacterData AFirstLightCharacterBase::GetCharacterData() const
{
	return CharacterData;
}

void AFirstLightCharacterBase::SetCharacterData(const FCharacterData& InCharacterData)
{
	CharacterData = InCharacterData;

	InitFromCharacterData(CharacterData, true);
}

void AFirstLightCharacterBase::InitFromCharacterData(const FCharacterData& InCharacterData, bool bFromReplication)
{
	
}

void AFirstLightCharacterBase::OnRep_CharacterData()
{
	InitFromCharacterData(CharacterData, true);
}

void AFirstLightCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFirstLightCharacterBase, CharacterData);
}

UFootstepsComponent* AFirstLightCharacterBase::GetFootstepsComponent() const
{
	return FootstepsComponent;
}
void AFirstLightCharacterBase::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->RemoveActiveEffectsWithTags(InAirTags);
	}
}

void AFirstLightCharacterBase::OnMaxMovementSpeedChanged(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
}
