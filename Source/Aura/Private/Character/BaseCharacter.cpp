// Copyright Catnap Software 2024


#include "Character/BaseCharacter.h"


ABaseCharacter::ABaseCharacter()
{

	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}



