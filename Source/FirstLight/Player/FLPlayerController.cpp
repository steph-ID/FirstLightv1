// Fill out your copyright notice in the Description page of Project Settings.


#include "FLPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FirstLight/Interaction/EnemyInterface.h"

AFLPlayerController::AFLPlayerController()
{
	bReplicates = true;
}

void AFLPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AFLPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	
	if(LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();
	}
}

void AFLPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(FLInputMappingContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(FLInputMappingContext, 0);
	
	PossessedPawn = GetPawn<APawn>();

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AFLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
 
	//Jumping
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AFLPlayerController::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AFLPlayerController::StopJump);

	//Moving
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFLPlayerController::Move);

	//Looking
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFLPlayerController::Look);

	//Crouching
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AFLPlayerController::Crouch);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AFLPlayerController::UnCrouch);

	//Crouching
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AFLPlayerController::Sprint);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AFLPlayerController::StopSprint);

	// Primary Attack
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AFLPlayerController::Attack);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &AFLPlayerController::StopAttack);

	// Action Bar
	//EnhancedInputComponent->BindAction(ActionBar_1, ETriggerEvent::Triggered, this, &AFirstLightPlayerController::Ability);
}

void AFLPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (PossessedPawn != nullptr)
	{
		PossessedPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		PossessedPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AFLPlayerController::Look(const FInputActionValue& Value)
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

void AFLPlayerController::Jump()
{
	/*FGameplayEventData Payload;

	Payload.Instigator = PossessedPawn;
	Payload.EventTag = PossessedPawn->JumpEventTag;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(PossessedPawn, Payload.EventTag, Payload);*/
}

void AFLPlayerController::StopJump()
{
}

void AFLPlayerController::Crouch()
{
	/*if (!GetCharacter()->GetCharacterMovement()->IsMovingOnGround()) { return; }
	if (GetCharacter())
	{
		GetCharacter()->Crouch();
	}*/
}

void AFLPlayerController::UnCrouch()
{
	/*if (GetCharacter())
	{
		GetCharacter()->UnCrouch();
	}*/
}

void AFLPlayerController::Sprint()
{
}

void AFLPlayerController::StopSprint()
{
}

void AFLPlayerController::Attack()
{
}

void AFLPlayerController::StopAttack()
{
}

void AFLPlayerController::AbilityCast()
{
}

void AFLPlayerController::StopAbilityCast()
{
}

void AFLPlayerController::Ability()
{
}
