// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstLightGameMode.h"

#include "FirstLightPlayerController.h"
#include "Core/FirstLightPlayerCharacter.h"
#include "GameFramework/SpectatorPawn.h"
#include "Kismet/GameplayStatics.h"

AFirstLightGameMode::AFirstLightGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/FirstLight/Characters/BP_FLChar"));

	//if (PlayerPawnBPClass.Class != NULL)
	/*if (static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/FirstLight/Characters/BP_FLChar")); PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
	RespawnDelay = 5.0f;

	PlayerClass = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Game/FirstLight/Characters/BP_FLChar.BP_FLChar_C"));
	if (!PlayerClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Failed to find PlayerClass. If it was moved, please update the reference location in C++."), *FString(__FUNCTION__));
	}
}

void AFirstLightGameMode::PlayerDied(AController* Controller)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ASpectatorPawn* SpectatorPawn = GetWorld()->SpawnActor<ASpectatorPawn>(SpectatorClass, Controller->GetPawn()->GetActorTransform(), SpawnParameters);

	Controller->UnPossess();
	Controller->Possess(SpectatorPawn);

	FTimerHandle RespawnTimerHandle;
	FTimerDelegate RespawnDelegate;

	RespawnDelegate = FTimerDelegate::CreateUObject(this, &AFirstLightGameMode::RespawnPlayer, Controller);
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, RespawnDelegate, RespawnDelay, false);

	AFirstLightPlayerController* PC = Cast<AFirstLightPlayerController>(Controller);
	if (PC)
	{
		PC->SetRespawnCountdown(RespawnDelay);
	}
}

void AFirstLightGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Get the enemy hero spawn point
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);
	for (AActor* Actor : Actors)
	{
		if (Actor->GetName() == FString("EnemyHeroSpawn"))
		{
			EnemySpawnPoint = Actor;
			break;
		}
	}
}

void AFirstLightGameMode::RespawnPlayer(AController * Controller)
{
	if (Controller->IsPlayerController())
	{
		// Respawn player hero
		AActor* PlayerStart = FindPlayerStart(Controller);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AFirstLightPlayerCharacter* Player = GetWorld()->SpawnActor<AFirstLightPlayerCharacter>(PlayerClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), SpawnParameters);

		APawn* OldSpectatorPawn = Controller->GetPawn();
		Controller->UnPossess();
		OldSpectatorPawn->Destroy();
		Controller->Possess(Player);
	}
	else
	{
		// Respawn AI hero
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AFirstLightPlayerCharacter* Player = GetWorld()->SpawnActor<AFirstLightPlayerCharacter>(PlayerClass, EnemySpawnPoint->GetActorTransform(), SpawnParameters);
		
		APawn* OldSpectatorPawn = Controller->GetPawn();
		Controller->UnPossess();
		OldSpectatorPawn->Destroy();
		Controller->Possess(Player);
	}
}