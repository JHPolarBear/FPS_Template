// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ThirdPerson/FPSCharacter_ThirdPerson.h"

#include "FPSAIController_ThirdPerson.h"
#include "Items/Weapons/FPSWeapon.h"

#include "StatComponent_ThirdPerson.h"

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

	// Create default weapon class
	DefaultWeaponClass = AFPSWeapon::StaticClass();

	// ai settings
	AIControllerClass = AFPSAIController_ThirdPerson::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	PatrolType = EPatrolType::PATROL_STILL;								// Default patrol type
	RandomMove_PatrolRadius = 1000.f;									// Default patrol radius

	// Create Character Level stat component
	CharacterStat = CreateDefaultSubobject<UStatComponent_ThirdPerson>(TEXT("CHARACTER_STAT"));

}

// Called when the game starts or when spawned
void AFPSCharacter_ThirdPerson::BeginPlay()
{
	Super::BeginPlay();

	if(DefaultWeaponClass != nullptr)
	{
		Weapon = GetWorld()->SpawnActor<AFPSWeapon>(DefaultWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if(Weapon)
			SetWeapon(Weapon);
	}
	
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

void AFPSCharacter_ThirdPerson::SetWeapon(AFPSWeapon* _weapon)
{
	FName WeaponSocket(TEXT("hand_rSocket"));
	if(_weapon != nullptr && GetMesh()->DoesSocketExist(WeaponSocket))
	{
		_weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
	}
	else
	{
		if(!GetMesh()->DoesSocketExist(WeaponSocket))
		{
			LOG_WARNING(TEXT("Failed to find socket"));
		}
		else
		{
			LOG_WARNING(TEXT("_weapon is empty"));
		}
	}

	return;

}

void AFPSCharacter_ThirdPerson::SetPatrolType(EPatrolType _type)
{
	PatrolType = _type;
}

const EPatrolType AFPSCharacter_ThirdPerson::GetPatrolType()
{
	return PatrolType;
}

bool AFPSCharacter_ThirdPerson::GetSinglePatrol_Position(FVector& VecPatrolPosition)
{
	if(SinglePatrol_Position == nullptr)
		return false;
	else
	{
		VecPatrolPosition = SinglePatrol_Position->GetActorLocation();
		return true;
	}	
}

