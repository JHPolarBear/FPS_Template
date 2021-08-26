// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSPlayerState.h"

AFPSPlayerState::AFPSPlayerState()
{
	Init();
}

void AFPSPlayerState::SetMaxHP(float _val)
{
	MaxHP = _val;
}

float AFPSPlayerState::GetMaxHP() const
{
	return MaxHP;
}

float AFPSPlayerState::GetCurrentHP() const
{
	return CurrentHP;
}

float AFPSPlayerState::GetHPRatio()
{
	if(CurrentHP <= 0)
		return 0;
	else
		return CurrentHP / MaxHP;
}

void AFPSPlayerState::SetMaxAP(float _val)
{
	MaxAP = _val;
}

float AFPSPlayerState::GetMaxAP() const
{
	return MaxAP;
}

float AFPSPlayerState::GetCurrentAP() const
{
	return CurrentAP;
}

float AFPSPlayerState::GetAPRatio()
{
	if(CurrentAP <= 0.f)
		return 0.f;
	else
		return CurrentAP / MaxAP;
}

void AFPSPlayerState::DecreaseAP()
{
	CurrentAP -= DecreaseAmountAP;
	CurrentAP = FMath::Clamp(CurrentAP, 0.f, MaxAP);
	OnPlayerStateChanged.Broadcast();
}

void AFPSPlayerState::IncreaseAP()
{
	CurrentAP += DecreaseAmountAP;
	CurrentAP = FMath::Clamp(CurrentAP, 0.f, MaxAP);
	OnPlayerStateChanged.Broadcast();
}

void AFPSPlayerState::SetRunMultiplier(float _val)
{
	RunMultiplier = _val;
}

float AFPSPlayerState::GetRunMultiplier()
{
	return RunMultiplier;
}

void AFPSPlayerState::SetDefaultWalkSpeed(float _val)
{
	DefaultWalkSpeed = _val;
}

float AFPSPlayerState::GetDefaultWalkSpeed()
{
	return DefaultWalkSpeed;
}

void AFPSPlayerState::Init()
{
	MaxHP = 100;
	MaxAP = 100;

	CurrentHP = 100;
	CurrentAP = 100;

	DecreaseAmountAP = 0.5;
}
