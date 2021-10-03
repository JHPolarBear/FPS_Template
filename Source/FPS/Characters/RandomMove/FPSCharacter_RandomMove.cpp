// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RandomMove/FPSCharacter_RandomMove.h"

#include "FPSAIController_RandomMove.h"

// Sets default values
AFPSCharacter_RandomMove::AFPSCharacter_RandomMove()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh_Static = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH_STATIC"));
	Mesh_Static->SetupAttachment(RootComponent);

	AIControllerClass = AFPSAIController_RandomMove::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AFPSCharacter_RandomMove::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSCharacter_RandomMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter_RandomMove::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

