// Fill out your copyright notice in the Description page of Project Settings.


#include "FLCharacter.h"

#include "FirstLight/Player/FLPlayerState.h"
#include "AbilitySystemComponent.h"
#include "FirstLight/AbilitySystem/FLAbilitySystemComponent.h"
#include "FirstLight/Player/FLPlayerController.h"
#include "FirstLight/UI/FLHUD.h"


AFLCharacter::AFLCharacter()
{
	/*CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0, 0, 150.0));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->FieldOfView = 80.0f;*/

	
}

void AFLCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void AFLCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void AFLCharacter::InitAbilityActorInfo()
{
	AFLPlayerState* FLPlayerState = GetPlayerState<AFLPlayerState>();
	check(FLPlayerState);
	FLPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(FLPlayerState, this);
	Cast<UFLAbilitySystemComponent>(FLPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = FLPlayerState->GetAbilitySystemComponent();
	AttributeSet = FLPlayerState->GetAttributeSet();

	// Create the player HUD
	if (AFLPlayerController* FLPlayerController = Cast<AFLPlayerController>(GetController()))
	{
		if (AFLHUD* FLHUD = Cast<AFLHUD>(FLPlayerController->GetHUD()))
		{
			FLHUD->InitOverlay(FLPlayerController, FLPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializePrimaryAttributes();
}