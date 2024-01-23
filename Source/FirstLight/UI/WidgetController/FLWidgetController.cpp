// Fill out your copyright notice in the Description page of Project Settings.


#include "FLWidgetController.h"

void UFLWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UFLWidgetController::BroadcastInitialValues()
{
}

void UFLWidgetController::BindCallbacksToDependencies()
{
}
