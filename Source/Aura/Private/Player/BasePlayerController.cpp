// Copyright Catnap Software 2024

#include "Player/BasePlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/HighlightInterface.h"

ABasePlayerController::ABasePlayerController()
{
	bReplicates = true;
}

void ABasePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	
}

void ABasePlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	/**
	 * Line Trace From Cursor - A bunch of things could happen:
	 * 1. LastActor = null && ThisActor = null
	 *		-- Nothing To Do, Not Hovering a Highlightable
	 * 2. LastActor = null && ThisActor = valid
	 *		-- Highlight ThisActor
	 * 3. LastActor = valid && ThisActor = null
	 *		-- UnHighlight LastActor
	 * 4. Both Actors Valid, but LastActor != ThisActor
	 *		-- UnHighlight LastActor, Hightlight ThisActor
	 * 5. Both Actors Valid, and same Actor
	 *		-- Nothing To Do, Already Hovering Actor
	 */

	if (LastActor == nullptr)
	{
		if(ThisActor != nullptr)
		{
			// #2
			ThisActor->HighlightActor();
		}
		else
		{
			// #1 - Both null, Nothing To Do
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// #3
			LastActor->UnHighlightActor();
		}
		else // Both Actors are Valid
		{
			if(LastActor != ThisActor)
			{
				// #4
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// #5 - Both Actors are the Same, Nothing To Do
			}
		}
	}
		
}


void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(PlayerContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(PlayerContext, 0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABasePlayerController::Move);	
}

void ABasePlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
	
}

