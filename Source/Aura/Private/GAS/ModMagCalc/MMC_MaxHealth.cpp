// Copyright Catnap Software 2024


#include "GAS/ModMagCalc/MMC_MaxHealth.h"

#include "GAS/BaseAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	ConDef.AttributeToCapture = UBaseAttributeSet::GetConstitutionAttribute();
	ConDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ConDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(ConDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Get Tags from Source & Target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Constitution = 0.f;
	GetCapturedAttributeMagnitude(ConDef, Spec, EvaluationParameters, Constitution);
	Constitution = FMath::Max<float>(Constitution, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return (3.f * (Constitution + 4.f)) * (PlayerLevel * 1.25);
}
