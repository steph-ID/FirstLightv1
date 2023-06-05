// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstLightPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "ActorComponents/FLCharacterMovementComponent.h"
#include "Core/FirstLightCharacterBase.h"
#include "Core/FirstLightPlayerState.h"
#include "FirstLight/AbilitySystem/FLAbilitySystemComponent.h"
#include "Widgets/FirstLightGameWidget.h"
#include "Widgets/FLDamageTextWidgetComponent.h"


AFirstLightPlayerController::AFirstLightPlayerController()
{
}

void AFirstLightPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	//GameModeRef = Cast<AFirstLightGameMode>(GetWorld()->GetAuthGameMode());
	//PossessedPawn = Cast<AFirstLightCharacter>(GetPawn());
	PossessedPawn = Cast<AFirstLightCharacterBase>(GetPawn());
	const AFirstLightPlayerState* FLPlayerState = GetPlayerState<AFirstLightPlayerState>();
	AbilitySystemComponent = FLPlayerState->GetAbilitySystemComponent();
}

void AFirstLightPlayerController::CreateHUD()
{
	// Only create once
	if (UIWidget)
	{
		return;
	}

	if (!UIWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing UIWidgetClass. Please fill in on the Blueprint of the PlayerController."), *FString(__FUNCTION__));
		return;
	}

	// Only create a HUD for local player
	if (!IsLocalPlayerController())
	{
		return;
	}

	// Need a valid FLPlayerState to get attributes from
	const AFirstLightPlayerState* FLPlayerState = GetPlayerState<AFirstLightPlayerState>();
	if (!FLPlayerState)
	{
		return;
	}

	UIWidget = CreateWidget<UFirstLightGameWidget>(this, UIWidgetClass);
	UIWidget->AddToViewport();

	// Set attributes
	UIWidget->SetCharacterLevel(FLPlayerState->GetCharacterLevel());
	UIWidget->SetExperience(FLPlayerState->GetXP());
	UIWidget->SetMaxExperience(FLPlayerState->GetMaxXP());
	UIWidget->SetCurrentHealth(FLPlayerState->GetHealth());
	UIWidget->SetMaxHealth(FLPlayerState->GetMaxHealth());
	UIWidget->SetHealthPercentage(FLPlayerState->GetHealth() / FMath::Max<float>(FLPlayerState->GetMaxHealth(), 1.f));
	UIWidget->SetCurrentMana(FLPlayerState->GetMana());
	UIWidget->SetMaxMana(FLPlayerState->GetMaxMana());
	UIWidget->SetManaPercentage(FLPlayerState->GetMana() / FMath::Max<float>(FLPlayerState->GetMaxMana(), 1.f));
	UIWidget->SetHealthRegenRate(FLPlayerState->GetHealthRegenRate());
	UIWidget->SetManaRegenRate(FLPlayerState->GetManaRegenRate());
	UIWidget->SetCurrentStamina(FLPlayerState->GetStamina());
	UIWidget->SetMaxStamina(FLPlayerState->GetMaxStamina());
	UIWidget->SetStaminaPercentage(FLPlayerState->GetStamina() / FMath::Max<float>(FLPlayerState->GetMaxStamina(), 1.f));
	UIWidget->SetStaminaRegenRate(FLPlayerState->GetStaminaRegenRate());
	UIWidget->SetGold(FLPlayerState->GetGold());
}

UFirstLightGameWidget* AFirstLightPlayerController::GetHUD() const
{
	return UIWidget;
}

void AFirstLightPlayerController::ShowDamageNumber_Implementation(float DamageAmount, AFirstLightCharacterBase* TargetCharacter)
{
	if (TargetCharacter && DamageNumberClass)
	{
		UFLDamageTextWidgetComponent* DamageText = NewObject<UFLDamageTextWidgetComponent>(TargetCharacter, DamageNumberClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->SetDamageText(DamageAmount);
	}
}

bool AFirstLightPlayerController::ShowDamageNumber_Validate(float DamageAmount, AFirstLightCharacterBase* TargetCharacter)
{
	return true;
}

void AFirstLightPlayerController::SetRespawnCountdown_Implementation(float RespawnTimeRemaining)
{
	if (UIWidget)
	{
		UIWidget->SetRespawnCountdown(RespawnTimeRemaining);
	}
}

bool AFirstLightPlayerController::SetRespawnCountdown_Validate(float RespawnTimeRemaining)
{
	return true;
}

void AFirstLightPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
 
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AFirstLightPlayerController::RequestJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AFirstLightPlayerController::RequestStopJump);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFirstLightPlayerController::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFirstLightPlayerController::Look);

		//Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AFirstLightPlayerController::RequestCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AFirstLightPlayerController::RequestUnCrouch);

		//Crouching
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AFirstLightPlayerController::RequestSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AFirstLightPlayerController::RequestStopSprint);

		// Primary Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AFirstLightPlayerController::RequestAttack);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &AFirstLightPlayerController::RequestStopAttack);

		// Action Bar
		//EnhancedInputComponent->BindAction(ActionBar_1, ETriggerEvent::Triggered, this, &AFirstLightPlayerController::RequestAbility);

	}
}

void AFirstLightPlayerController::RequestAbility()
{
}

void AFirstLightPlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (PossessedPawn != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = PossessedPawn->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		PossessedPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		PossessedPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AFirstLightPlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (PossessedPawn != nullptr)
	{
		// add yaw and pitch input to controller
		PossessedPawn->AddControllerYawInput(LookAxisVector.X);
		PossessedPawn->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFirstLightPlayerController::RequestCrouch()
{
	if (!GetCharacter()->GetCharacterMovement()->IsMovingOnGround()) { return; }
	if (GetCharacter())
	{
		GetCharacter()->Crouch();
	}
}

void AFirstLightPlayerController::RequestUnCrouch()
{
	if (GetCharacter())
	{
		GetCharacter()->UnCrouch();
	}
}

void AFirstLightPlayerController::RequestJump()
{
	FGameplayEventData Payload;

	Payload.Instigator = PossessedPawn;
	Payload.EventTag = PossessedPawn->JumpEventTag;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(PossessedPawn, Payload.EventTag, Payload);
		//AbilitySystemComponent->CancelAbilities(PossessedPawn->JumpEventTag);
	//printf_s("this is a jump.");
}

void AFirstLightPlayerController::RequestStopJump()
{
	/*if (GetCharacter())
	{
		//GetCharacter()->StopJumping();
	}*/
}

void AFirstLightPlayerController::RequestAttack()
{
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->TryActivateAbilitiesByTag(PossessedPawn->CombatTags);
	}
}

void AFirstLightPlayerController::RequestStopAttack()
{
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAbilities(&PossessedPawn->CombatTags);
	}
}

void AFirstLightPlayerController::RequestCast()
{
}

void AFirstLightPlayerController::RequestStopCast()
{
}

void AFirstLightPlayerController::RequestSprint()
{
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->TryActivateAbilitiesByTag(PossessedPawn->SprintTags);
	}
	/*UFLCharacterMovementComponent* MovementComp = Cast<UFLCharacterMovementComponent>(PossessedPawn->GetMovementComponent());
	MovementComp->StartSprinting();
	MovementComp->GetMaxSpeed();*/
}

void AFirstLightPlayerController::RequestStopSprint()
{
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAbilities(&PossessedPawn->SprintTags);
	}
	/*UFLCharacterMovementComponent* MovementComp = Cast<UFLCharacterMovementComponent>(PossessedPawn->GetMovementComponent());
	MovementComp->StopSprinting();*/
}

// Server only
void AFirstLightPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AFirstLightPlayerState* FLPlayerState = GetPlayerState<AFirstLightPlayerState>();
	if (FLPlayerState)
	{
		// Init ASC with FLPlayerState (Owner) and our new Pawn (AvatarActor)
		FLPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(FLPlayerState, InPawn);
	}
}

void AFirstLightPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// For edge cases where the FLPlayerState is repped before the character is possessed.
	CreateHUD();
}
