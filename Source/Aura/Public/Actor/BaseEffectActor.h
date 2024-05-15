// Copyright Catnap Software 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEffectActor.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AURA_API ABaseEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseEffectActor();

	

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGamePlayEffectClass;

	
	


	



};
