// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FirstLightGameTypes.h"
#include "FootstepsComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTLIGHT_API UFootstepsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFootstepsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FName LeftFootSocketName = TEXT("ball_l");
	
	UPROPERTY(EditAnywhere)
	FName RightFootSocketName = TEXT("ball_r");
	
public:	
	void HandleFootstep(EFoot Foot);
	
};
