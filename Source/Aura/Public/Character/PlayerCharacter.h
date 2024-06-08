// Copyright Catnap Software 2024

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	//** Combat Interface **//
	
	virtual int32 GetPlayerLevel() override;
	
	//** End Combat Interface **//
private:
	void InitAbilityActorInfo() override;
	
};
