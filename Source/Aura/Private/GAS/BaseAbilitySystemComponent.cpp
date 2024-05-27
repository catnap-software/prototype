// Copyright Catnap Software 2024

#include "GAS/BaseAbilitySystemComponent.h"


void UBaseAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UBaseAbilitySystemComponent::EffectApplied);
}

void UBaseAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	for (const FGameplayTag& Tag : TagContainer)
	{
		
	//TODO: Broadcast the tag to the WidgetController

	const FString Msg = FString::Printf(TEXT("Gameplay Effect Tag: %s"), *Tag.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, Msg);
		
	}
}
