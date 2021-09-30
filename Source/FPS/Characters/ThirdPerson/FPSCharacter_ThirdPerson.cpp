// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ThirdPerson/FPSCharacter_ThirdPerson.h"

// Sets default values
AFPSCharacter_ThirdPerson::AFPSCharacter_ThirdPerson()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UAnimInstance> _ANIM(TEXT("AnimBlueprint'/Game/ThirdPerson/Animations/AnimBlueprint_ThirdPerson.AnimBlueprint_ThirdPerson_C'"));
	if(_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(_ANIM.Class);
	}

}

// Called when the game starts or when spawned
void AFPSCharacter_ThirdPerson::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSCharacter_ThirdPerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter_ThirdPerson::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

