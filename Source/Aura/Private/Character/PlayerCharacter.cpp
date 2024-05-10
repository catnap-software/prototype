// Copyright Catnap Software 2024


#include "Character/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/BasePlayerState.h"

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

void APlayerCharacter::InitAbilityActorInfo()
{
	ABasePlayerState* BasePlayerState = GetPlayerState<ABasePlayerState>();
	check(BasePlayerState);
	BasePlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(BasePlayerState, this);
	AbilitySystemComponent = BasePlayerState->GetAbilitySystemComponent();
	AttributeSet = BasePlayerState->GetAttributeSet();
}
