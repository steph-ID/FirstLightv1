// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Core/FirstLightCharacter.h"
#include "FirstLightGameMode.h"
#include "FirstLightPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API AFirstLightPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Crouch Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CrouchAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ActionBar_1;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ActionBar_2;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ActionBar_3;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ActionBar_4;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ActionBar_5;

	UAbilitySystemComponent* AbilitySystemComponent;

public:

	AFirstLightPlayerController();
	
	//--- Overrides
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	
	void CreateHUD();
	class UFirstLightGameWidget* GetHUD() const;

	UPROPERTY(EditAnywhere, Category = "First Light|UI")
	TSubclassOf<class UFLDamageTextWidgetComponent> DamageNumberClass;

	UFUNCTION(Client, Reliable, WithValidation)
	void ShowDamageNumber(float DamageAmount, AFirstLightCharacterBase* TargetCharacter);
	void ShowDamageNumber_Implementation(float DamageAmount, AFirstLightCharacterBase* TargetCharacter);
	bool ShowDamageNumber_Validate(float DamageAmount, AFirstLightCharacterBase* TargetCharacter);

	// Simple way to RPC to the client the countdown until they respawn from the GameMode. Will be latency amount of out sync with the Server.
	UFUNCTION(Client, Reliable, WithValidation)
	void SetRespawnCountdown(float RespawnTimeRemaining);
	void SetRespawnCountdown_Implementation(float RespawnTimeRemaining);
	bool SetRespawnCountdown_Validate(float RespawnTimeRemaining);

	UPROPERTY(BlueprintReadWrite)
	AFirstLightCharacter* PossessedPawn;
	
	//--- Input Actions
	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void RequestJump();
	
	UFUNCTION(BlueprintCallable)
	void RequestStopJump();

	UFUNCTION(BlueprintCallable)
	void RequestCrouch();
	
	UFUNCTION(BlueprintCallable)
	void RequestUnCrouch();

	UFUNCTION(BlueprintCallable)
	void RequestSprint();
	
	UFUNCTION(BlueprintCallable)
	void RequestStopSprint();

	UFUNCTION(BlueprintCallable)
	void RequestAttack();
	
	UFUNCTION(BlueprintCallable)
	void RequestStopAttack();

	UFUNCTION(BlueprintCallable)
	void RequestCast();
	
	UFUNCTION(BlueprintCallable)
	void RequestStopCast();
	
	UFUNCTION(BlueprintCallable)
	void RequestAbility();
	
	//AFirstLightGameMode* GameModeRef;
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "First Light|UI")
	TSubclassOf<class UFirstLightGameWidget> UIWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "First Light|UI")
	class UFirstLightGameWidget* UIWidget;

	// Server only
	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnRep_PlayerState() override;

};
