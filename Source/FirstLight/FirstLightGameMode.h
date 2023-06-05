// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FirstLightGameMode.generated.h"

UCLASS()
class AFirstLightGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AFirstLightGameMode();

	void PlayerDied(AController* Controller);

protected:
	float RespawnDelay;

	//TSubclassOf<class AFirstLightCharacter> PlayerClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "First Light")
	TSubclassOf<class AFirstLightPlayerCharacter> PlayerClass;

	AActor* EnemySpawnPoint;

	virtual void BeginPlay() override;

	void RespawnPlayer(AController* Controller);
};



