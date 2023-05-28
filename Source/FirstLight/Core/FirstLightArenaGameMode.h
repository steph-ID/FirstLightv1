// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstLight/FirstLightGameMode.h"
#include "FirstLight/Widgets/FirstLightGameWidget.h"
#include "FirstLightArenaGameMode.generated.h"

class ULevelSequence;

UENUM(BlueprintType)
enum class EGameState : uint8
{
	None		UMETA(DisplayName = "None"),
	Waiting		UMETA(DisplayName = "Waiting"),
	Playing		UMETA(DisplayName = "Playing"),
	Results		UMETA(DisplayName = "Results"),
	GameOver	UMETA(DisplayName = "GameOver"),
};
	
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStart);

/**
 * 
 */
UCLASS()
class FIRSTLIGHT_API AFirstLightArenaGameMode : public AFirstLightGameMode
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	EGameState GetCurrentGameState() const;
	void BossDefeated();

	UFUNCTION(BlueprintCallable)
	void StartGame();
	
public:
	AFirstLightArenaGameMode();

private:

	// --- VARS --- //

	// Create and set CurrentGameState to NONE. This will be tracked in the code file. 
	UPROPERTY(VisibleAnywhere, Category = "First Light|States")
	EGameState CurrentGameState = EGameState::None;
	
	
	// --- Game Start Countdown
	FTimerHandle WaitModeTimerHandle;
	
	// Countdown before gameplay state begins. Exposed so we can easily change this in BP editor. 
	UPROPERTY(EditAnywhere, Category = "First Light|Game Details")
	float GameCountdownDuration = 5.0f;

	void DisplayCountdown();
	
	UPROPERTY()
	UFirstLightGameWidget* GameWidget; // Object we'll be creating and adding to the Viewport
	
	UPROPERTY(EditAnywhere, Category = "First Light|Widget")
	TSubclassOf<UFirstLightGameWidget> GameWidgetClass; // Exposed class to check the type of widget to display
	
	UPROPERTY(EditAnywhere, Category = "First Light|Level Sequences")
	ULevelSequence* ArenaGateAsset = nullptr;
	
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Default")
	FGameStart GameStart;
	
	APlayerController* PC = nullptr;
	
protected:

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Light|Level Sequences")
	ULevelSequencePlayer* LevelSequencePlayer;*/

	//void OnLevelSequenceFinished();

	void SpawnBoss();
	void ShowResults();
};
