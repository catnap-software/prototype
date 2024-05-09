// Copyright Catnap Software 2024

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Interaction/HighlightInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacter : public ABaseCharacter, public IHighlightInterface
{
	GENERATED_BODY()

public:
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false; 
};
