// Copyright Catnap Software 2024

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

class UAbilitySystemComponent;
class UOverlayWidgetController;
class UBaseUserWidget;
struct FWidgetControllerParams;

/**
 * 
 */
UCLASS()
class AURA_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
public:

	UPROPERTY()
	TObjectPtr<UBaseUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	
protected:

	
	
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBaseUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
};
