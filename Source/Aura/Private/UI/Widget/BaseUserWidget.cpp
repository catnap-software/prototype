// Copyright Catnap Software 2024


#include "UI/Widget/BaseUserWidget.h"

void UBaseUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetContollerSet();
}
