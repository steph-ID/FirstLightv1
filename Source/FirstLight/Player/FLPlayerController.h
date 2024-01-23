// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FLPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;

/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API AFLPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFLPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadWrite)
	APawn* PossessedPawn = nullptr;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> FLInputMappingContext;

	/** Movement Input Actions */
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> SprintAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> AttackAction;

	/** Action Bar Input Actions */
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ActionBar_1;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ActionBar_2;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ActionBar_3;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ActionBar_4;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ActionBar_5;

	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& InputActionValue);

	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Jump();
	
	UFUNCTION(BlueprintCallable)
	void StopJump();

	UFUNCTION(BlueprintCallable)
	void Crouch();
	
	UFUNCTION(BlueprintCallable)
	void UnCrouch();

	UFUNCTION(BlueprintCallable)
	void Sprint();
	
	UFUNCTION(BlueprintCallable)
	void StopSprint();

	UFUNCTION(BlueprintCallable)
	void Attack();
	
	UFUNCTION(BlueprintCallable)
	void StopAttack();

	UFUNCTION(BlueprintCallable)
	void AbilityCast();
	
	UFUNCTION(BlueprintCallable)
	void StopAbilityCast();
	
	UFUNCTION(BlueprintCallable)
	void Ability();

	void CursorTrace();
	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
};
