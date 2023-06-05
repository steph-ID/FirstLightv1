// Copyright 2020 Dan Kestranek.


#include "FLCharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "FirstLight/Core/FirstLightCharacterBase.h"
#include "GameplayTagContainer.h"

UFLCharacterMovementComponent::UFLCharacterMovementComponent()
{
	/*SprintSpeedMultiplier = 1.4f;
	ADSSpeedMultiplier = 0.5f;*/
}

/*float UFLCharacterMovementComponent::GetMaxSpeed() const
{
	AFirstLightCharacterBase* Owner = Cast<AFirstLightCharacterBase>(GetOwner());
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() No Owner"), *FString(__FUNCTION__));
		return Super::GetMaxSpeed();
	}

	if (!Owner->IsAlive())
	{
		return 0.0f;
	}

	if (Owner->GetAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun"))))
	{
		return 0.0f;
	}

	if (RequestToStartSprinting)
	{
		return Owner->GetMoveSpeed() * SprintSpeedMultiplier;
	}

	if (RequestToStartADS)
	{
		return Owner->GetMoveSpeed() * ADSSpeedMultiplier;
	}

	return Owner->GetMoveSpeed();
}

void UFLCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	//The Flags parameter contains the compressed input flags that are stored in the saved move.
	//UpdateFromCompressed flags simply copies the flags from the saved move into the movement component.
	//It basically just resets the movement component to the state when the move was made so it can simulate from there.
	RequestToStartSprinting = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;

	RequestToStartADS = (Flags & FSavedMove_Character::FLAG_Custom_1) != 0;
}

FNetworkPredictionData_Client* UFLCharacterMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != NULL);

	if (!ClientPredictionData)
	{
		UFLCharacterMovementComponent* MutableThis = const_cast<UFLCharacterMovementComponent*>(this);

		MutableThis->ClientPredictionData = new FFLNetworkPredictionData_Client(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
	}

	return ClientPredictionData;
}

void UFLCharacterMovementComponent::StartSprinting()
{
	RequestToStartSprinting = true;
}

void UFLCharacterMovementComponent::StopSprinting()
{
	RequestToStartSprinting = false;
}

void UFLCharacterMovementComponent::StartAimDownSights()
{
	RequestToStartADS = true;
}

void UFLCharacterMovementComponent::StopAimDownSights()
{
	RequestToStartADS = false;
}

void UFLCharacterMovementComponent::FFLSavedMove::Clear()
{
	Super::Clear();

	SavedRequestToStartSprinting = false;
	SavedRequestToStartADS = false;
}

uint8 UFLCharacterMovementComponent::FFLSavedMove::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if (SavedRequestToStartSprinting)
	{
		Result |= FLAG_Custom_0;
	}

	if (SavedRequestToStartADS)
	{
		Result |= FLAG_Custom_1;
	}

	return Result;
}

bool UFLCharacterMovementComponent::FFLSavedMove::CanCombineWith(const FSavedMovePtr & NewMove, ACharacter * Character, float MaxDelta) const
{
	//Set which moves can be combined together. This will depend on the bit flags that are used.
	if (SavedRequestToStartSprinting != ((FFLSavedMove*)&NewMove)->SavedRequestToStartSprinting)
	{
		return false;
	}

	if (SavedRequestToStartADS != ((FFLSavedMove*)&NewMove)->SavedRequestToStartADS)
	{
		return false;
	}

	return Super::CanCombineWith(NewMove, Character, MaxDelta);
}

void UFLCharacterMovementComponent::FFLSavedMove::SetMoveFor(ACharacter * Character, float InDeltaTime, FVector const & NewAccel, FNetworkPredictionData_Client_Character & ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	UFLCharacterMovementComponent* CharacterMovement = Cast<UFLCharacterMovementComponent>(Character->GetCharacterMovement());
	if (CharacterMovement)
	{
		SavedRequestToStartSprinting = CharacterMovement->RequestToStartSprinting;
		SavedRequestToStartADS = CharacterMovement->RequestToStartADS;
	}
}

void UFLCharacterMovementComponent::FFLSavedMove::PrepMoveFor(ACharacter * Character)
{
	Super::PrepMoveFor(Character);

	UFLCharacterMovementComponent* CharacterMovement = Cast<UFLCharacterMovementComponent>(Character->GetCharacterMovement());
	if (CharacterMovement)
	{
	}
}

UFLCharacterMovementComponent::FFLNetworkPredictionData_Client::FFLNetworkPredictionData_Client(const UCharacterMovementComponent & ClientMovement)
	: Super(ClientMovement)
{
}

FSavedMovePtr UFLCharacterMovementComponent::FFLNetworkPredictionData_Client::AllocateNewMove()
{
	return FSavedMovePtr(new FFLSavedMove());
}*/