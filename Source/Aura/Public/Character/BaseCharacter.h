// Copyright Catnap Software 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS(Abstract)
class AURA_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;


};
