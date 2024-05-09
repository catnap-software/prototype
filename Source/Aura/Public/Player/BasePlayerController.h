// Copyright Catnap Software 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IHighlightInterface;

/**
 * 
 */
UCLASS()
class AURA_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> PlayerContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();

	TScriptInterface<IHighlightInterface> LastActor;
	TScriptInterface<IHighlightInterface> ThisActor;
	
};
