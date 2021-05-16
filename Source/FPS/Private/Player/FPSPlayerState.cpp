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

float AFPSPlayerState::GetHPRatio()
{
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

float AFPSPlayerState::GetAPRatio()
{
	return CurrentAP / MaxAP;
}

void AFPSPlayerState::Init()
{
	MaxHP = 100;
	MaxAP = 100;

	CurrentHP = 100;
	CurrentAP = 80;
}
