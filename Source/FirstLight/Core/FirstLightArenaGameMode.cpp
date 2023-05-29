// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstLightArenaGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "FirstLight/Widgets/FirstLightGameWidget.h"

AFirstLightArenaGameMode::AFirstLightArenaGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/FirstLight/Characters/BP_FLChar"));

	//if (PlayerPawnBPClass.Class != NULL)
	/*if (static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/FirstLight/Characters/BP_FLChar")); PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}

void AFirstLightArenaGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AFirstLightArenaGameMode::NewArenaGame()
{
	CurrentGameState = EGameState::Waiting;
	DisplayCountdown();

	GetWorld()->GetTimerManager().SetTimer(WaitModeTimerHandle, this, &AFirstLightArenaGameMode::StartGame, GameCountdownDuration, false);
}

EGameState AFirstLightArenaGameMode::GetCurrentGameState() const
{
	return CurrentGameState;
}

void AFirstLightArenaGameMode::BossDefeated()
{
	CurrentGameState = EGameState::GameOver;

	GameWidget->LevelComplete();
	FInputModeUIOnly InputMode;
	PC->SetInputMode(InputMode);
	PC->SetShowMouseCursor(true);
}

void AFirstLightArenaGameMode::DisplayCountdown()
{
	if(!GameWidgetClass) {return;}

	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	GameWidget = CreateWidget<UFirstLightGameWidget>(PC, GameWidgetClass);
	GameWidget->AddToViewport();
	GameWidget->StartCountdown(GameCountdownDuration, this); // Will crash multiplayer
}

void AFirstLightArenaGameMode::StartGame()
{
	CurrentGameState = EGameState::Playing;
	GameStart.Broadcast();
	
	/*ALevelSequenceActor* SequenceActor = nullptr;
	
	if (ArenaGateAsset && LevelSequencePlayer == nullptr)
		LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), ArenaGateAsset, FMovieSceneSequencePlaybackSettings(), SequenceActor);
    
	//Sequence Play
	if (LevelSequencePlayer)
	{
		LevelSequencePlayer->Play();
	}*/
	
	FInputModeGameOnly InputMode;
	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->SetInputMode(InputMode);
	PC->SetShowMouseCursor(false);
}

void AFirstLightArenaGameMode::SpawnBoss()
{
}

void AFirstLightArenaGameMode::ShowResults()
{
}

/*void AFirstLightArenaGameMode::OnLevelSequenceFinished()
{
	// Unbind the on finished event delegate if needed
	if (LevelSequencePlayer)
	{
		LevelSequencePlayer->OnFinished.RemoveDynamic(this, &AFirstLightGameMode::OnLevelSequenceFinished);
	}
}*/

