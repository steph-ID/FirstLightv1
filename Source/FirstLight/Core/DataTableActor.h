// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "DataTableActor.generated.h"

/*UENUM(BlueprintType)
enum class ELeaderboardDT : uint8
{
	Name			UMETA(DisplayName = "Name"),
	Score 			UMETA(DisplayName = "Score"),
	Time 			UMETA(DisplayName = "Time"),
};*/

USTRUCT(BlueprintType)
struct FLeaderboardData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString PlayerName = "";

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int PlayerScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PlayerTime = 0.f;
};

UCLASS()
class FIRSTLIGHT_API ADataTableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADataTableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
	class UDataTable* LeaderboardTable;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
	FString PlayerName = "Player";
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
	int PlayerScore = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
	float PlayerTime = 0.f;

};
