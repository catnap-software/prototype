// Copyright Catnap Software 2024


#include "Character/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/BaseAbilitySystemComponent.h"
#include "Player/BasePlayerController.h"
#include "Player/BasePlayerState.h"
#include "UI/HUD/BaseHUD.h"

class ABaseHUD;

APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//** InitAbilityActorInfo For SERVERSIDE, Needs Pawn Possession
	InitAbilityActorInfo();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//** InitAbilityActorInfo For CLIENTSIDE, Needs Playerstate
	InitAbilityActorInfo();
	
}

int32 APlayerCharacter::GetPlayerLevel()
{
	const ABasePlayerState* BasePlayerState = GetPlayerState<ABasePlayerState>();
	check (BasePlayerState);
	return BasePlayerState->GetPlayerLevel();
	
}

void APlayerCharacter::InitAbilityActorInfo()
{
	ABasePlayerState* BasePlayerState = GetPlayerState<ABasePlayerState>();
	check(BasePlayerState);
	BasePlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(BasePlayerState, this);
	Cast<UBaseAbilitySystemComponent>(BasePlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = BasePlayerState->GetAbilitySystemComponent();
	AttributeSet = BasePlayerState->GetAttributeSet();

	if (ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(GetController()))
	{
		if (ABaseHUD* BaseHUD = Cast<ABaseHUD>(BasePlayerController->GetHUD()))
		{
			BaseHUD->InitOverlay(BasePlayerController, BasePlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}
