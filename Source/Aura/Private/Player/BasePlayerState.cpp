// Copyright Catnap Software 2024


#include "Player/BasePlayerState.h"
#include "GAS/BaseAbilitySystemComponent.h"
#include "GAS/BaseAttributeSet.h"
#include "Net/UnrealNetwork.h"

ABasePlayerState::ABasePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f;
}

void ABasePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABasePlayerState, Level);
}

UAbilitySystemComponent* ABasePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABasePlayerState::PossessedBy()
{
}

void ABasePlayerState::OnRep_Level(int32 OldLevel)
{
}
