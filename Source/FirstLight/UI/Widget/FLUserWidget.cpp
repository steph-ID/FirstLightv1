// Fill out your copyright notice in the Description page of Project Settings.


#include "FLUserWidget.h"

void UFLUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
