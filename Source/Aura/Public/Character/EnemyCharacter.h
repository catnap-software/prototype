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
	AEnemyCharacter();


	/** Enemy Interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** End Enemy Interface */


	//** Combat Interface **//
	virtual int32 GetPlayerLevel() override;
	
	//** End Combat Interface **//
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};




