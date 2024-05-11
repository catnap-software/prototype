// Copyright Catnap Software 2024


#include "Actor/BaseEffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Components/SphereComponent.h"
#include "GAS/BaseAttributeSet.h"



ABaseEffectActor::ABaseEffectActor()
{
 
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
	
}

void ABaseEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Change This to apply a Gameplay Effect. Right now we're using const_cast as a hack and it is trash coding :(
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UBaseAttributeSet* BaseAttributeSet = Cast<UBaseAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UBaseAttributeSet::StaticClass()));
		
		UBaseAttributeSet* MutableBaseAttributeSet = const_cast<UBaseAttributeSet*>(BaseAttributeSet);
		MutableBaseAttributeSet->SetHealth(BaseAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void ABaseEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}


void ABaseEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ABaseEffectActor::EndOverlap);
}
