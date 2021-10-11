// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ThirdPerson/FPSCharacter_ThirdPerson.h"

#include "Components/WidgetComponent.h"

#include "FPSAIController_ThirdPerson.h"
#include "Items/Weapons/FPSWeapon.h"

#include "StatComponent_ThirdPerson.h"

#include "UI/Characters/CharacterStat_Widget.h"

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

	// Initialize Widget Components
	StatBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("STAT_BARWIDGET"));
	StatBarWidget->SetupAttachment(GetMesh());

	StatBarWidget->SetRelativeLocation(FVector(0.f, 0.f, 205.f));
	StatBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_STATBAR(TEXT("WidgetBlueprint'/Game/UI/Characters/UI_NPC_StatBar.UI_NPC_StatBar_C'"));
	if(UI_STATBAR.Succeeded())
	{
		StatBarWidget->SetWidgetClass(UI_STATBAR.Class);
		StatBarWidget->SetDrawSize(FVector2D(130, 25.f));
	}

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

	auto CharaterStatWidget = Cast<UCharacterStat_Widget>(StatBarWidget->GetUserWidgetObject());
	if (CharaterStatWidget != nullptr)
	{
		CharaterStatWidget->BindCharacterStat(CharacterStat);
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

void AFPSCharacter_ThirdPerson::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

float AFPSCharacter_ThirdPerson::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	LOG_WARNING(TEXT("Damage Occured : %f"), FinalDamage);

	CharacterStat->SetDamage(FinalDamage);

	return FinalDamage;
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

