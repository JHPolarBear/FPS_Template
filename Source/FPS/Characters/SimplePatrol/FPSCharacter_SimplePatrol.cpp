// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter_SimplePatrol.h"
#include "FPSAIController_SimplePatrol.h"

// Sets default values
AFPSCharacter_SimplePatrol::AFPSCharacter_SimplePatrol()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh_Static = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH_STATIC"));
	Mesh_Static->SetupAttachment(RootComponent);

	AIControllerClass = AFPSAIController_SimplePatrol::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AFPSCharacter_SimplePatrol::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSCharacter_SimplePatrol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter_SimplePatrol::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// 랠리 포인트의 좌표를 리턴
bool AFPSCharacter_SimplePatrol::GetRallyPoint_Pos(FVector& _pos)
{
	if (RallyPoint)
	{
		_pos = RallyPoint->GetActorLocation();

		return true;
	}

	return false;
}

