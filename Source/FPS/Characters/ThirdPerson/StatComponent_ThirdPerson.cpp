// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ThirdPerson/StatComponent_ThirdPerson.h"

// Sets default values for this component's properties
UStatComponent_ThirdPerson::UStatComponent_ThirdPerson()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// set this value to true to use InitializeComponent function
	bWantsInitializeComponent = true;

	// ...

	// Default Level
	Level = 1;

}


// Called when the game starts
void UStatComponent_ThirdPerson::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UStatComponent_ThirdPerson::InitializeComponent()
{
	Super::InitializeComponent();

	Init();
}

void UStatComponent_ThirdPerson::Init()
{
	// set level 1 as default
	SetNewLevel(1, true);

	DecreaseAmountAP = 0.5;
}

void UStatComponent_ThirdPerson::SetNewLevel(int32 _NewLevel, bool _RefreshCurrentStat /*= false*/)
{
	auto FPSGameInstance = Cast<UFPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	ASSERT_CHECK(FPSGameInstance != nullptr);

	// Get Character level info from game instance
	CurrentLevelData = FPSGameInstance->GetCharacterLevelData(_NewLevel);

	if (CurrentLevelData != nullptr)
	{
		Level = _NewLevel;

		// 현재 HP/AP를 갱신시키는 경우 풀로 체워준다
		if(_RefreshCurrentStat)
		{
			SetCurrentHP(CurrentLevelData->MaxHP);
			SetCurrentAP(CurrentLevelData->MaxAP);
		}
	}
}

float UStatComponent_ThirdPerson::GetMaxHP() const
{
	return CurrentLevelData->MaxHP;
}

void UStatComponent_ThirdPerson::SetCurrentHP(float _newHP)
{
	CurrentHP = _newHP;

	// Broadcast
	OnCharacterStatChanged.Broadcast();

	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnCharacterHPZero.Broadcast();
	}
}

float UStatComponent_ThirdPerson::GetCurrentHP() const
{
	return CurrentHP;
}

float UStatComponent_ThirdPerson::GetHPRatio()
{
	if (CurrentHP <= 0)
		return 0;
	else
		return CurrentHP / CurrentLevelData->MaxHP;
}

void UStatComponent_ThirdPerson::SetDamage(float _damage)
{
	ASSERT_CHECK(CurrentLevelData != nullptr);

	SetCurrentHP(FMath::Clamp(CurrentHP - _damage, 0.f, CurrentLevelData->MaxHP));
}

float UStatComponent_ThirdPerson::GetMaxAP() const
{
	return CurrentLevelData->MaxAP;
}

void UStatComponent_ThirdPerson::SetCurrentAP(float _newAP)
{
	CurrentAP = _newAP;

	OnCharacterStatChanged.Broadcast();

	if(CurrentAP < KINDA_SMALL_NUMBER)
	{
		CurrentAP = 0.f;

		OnCharacterHPZero.Broadcast();
	}
}

float UStatComponent_ThirdPerson::GetCurrentAP() const
{
	return CurrentAP;
}

float UStatComponent_ThirdPerson::GetAPRatio()
{
	if (CurrentAP <= 0)
		return 0;
	else
		return CurrentAP / CurrentLevelData->MaxAP;
}

void UStatComponent_ThirdPerson::DecreaseAP()
{
	CurrentAP -= DecreaseAmountAP;
	CurrentAP = FMath::Clamp(CurrentAP, 0.f, CurrentLevelData->MaxAP);
}

void UStatComponent_ThirdPerson::IncreaseAP()
{
	CurrentAP += DecreaseAmountAP;
	CurrentAP = FMath::Clamp(CurrentAP, 0.f, CurrentLevelData->MaxAP);
}

void UStatComponent_ThirdPerson::SetRunMultiplier(float _val)
{
	RunMultiplier = _val;
}

float UStatComponent_ThirdPerson::GetRunMultiplier()
{
	return RunMultiplier;
}

void UStatComponent_ThirdPerson::SetDefaultWalkSpeed(float _val)
{
	DefaultWalkSpeed = _val;
}

float UStatComponent_ThirdPerson::GetDefaultWalkSpeed()
{
	return DefaultWalkSpeed;
}
