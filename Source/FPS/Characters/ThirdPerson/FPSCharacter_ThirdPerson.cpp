// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ThirdPerson/FPSCharacter_ThirdPerson.h"

#include "Components/WidgetComponent.h"

#include "Animations/ThirdPerson/AnimInstance_ThirdPerson.h"

#include "FPSAIController_ThirdPerson.h"
#include "Items/Weapons/FPSWeapon.h"

#include "StatComponent_ThirdPerson.h"

#include "UI/Characters/CharacterStat_Widget.h"

// Sets default values
AFPSCharacter_ThirdPerson::AFPSCharacter_ThirdPerson()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Default Skeletal Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MAN(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if(SK_MAN.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_MAN.Object);
	}

	// Set Anim Instance
	static ConstructorHelpers::FClassFinder<UAnimInstance> _ANIM(TEXT("/Game/AnimStarterPack/UE4ASP_HeroTPP_AnimBlueprint.UE4ASP_HeroTPP_AnimBlueprint_C"));
	if(_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(_ANIM.Class);
	}

	// Set collision profile
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

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

	DeadTimer = 3.f;

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

	// Bind character stat widget with character stat component
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

	// Add dead animation to character stat component's delegate
	auto Anim = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());
	ASSERT_CHECK(Anim != nullptr);

	CharacterStat->OnCharacterHPZero.AddLambda([this]()-> void{
		LOG_WARNING(TEXT("Character dead anim"));

		OnDead();
	});
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

		_weapon->SetOwner(this);
		Weapon = _weapon;
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

void AFPSCharacter_ThirdPerson::OnDead()
{	
	GetController()->StopMovement();
	GetController()->UnPossess();

	// set properties to not interact with user's action
	SetActorEnableCollision(false);

	GetController()->StopMovement();
	GetController()->UnPossess();

	GetMesh()->SetHiddenInGame(false);
	SetCanBeDamaged(false);

	// set dead flag to anim instance
	UAnimInstance_ThirdPerson* _Anim = Cast<UAnimInstance_ThirdPerson>(GetMesh()->GetAnimInstance());
	if(_Anim)
	{
		_Anim->SetIsDead(true);
	}

	// hide widget
	StatBarWidget->SetHiddenInGame(true);

	GetWorld()->GetTimerManager().SetTimer(DeadActionHandler, this, &AFPSCharacter_ThirdPerson::OnDeadAction, DeadTimer, false);
}

void AFPSCharacter_ThirdPerson::OnDeadAction()
{
	if (Weapon)
		Weapon->Destroy();

	// Simply destroy character
	Destroy();
}

