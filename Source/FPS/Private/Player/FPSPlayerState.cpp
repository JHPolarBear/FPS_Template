// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSPlayerState.h"

AFPSPlayerState::AFPSPlayerState()
{
	MaxHP = 0;
	MaxAP = 0;
}

void AFPSPlayerState::SetMaxHP(float _val)
{
	MaxHP = _val;
}

float AFPSPlayerState::GetMaxHP() const
{
	return MaxHP;
}

void AFPSPlayerState::SetMaxAP(float _val)
{
	MaxAP = _val;
}

float AFPSPlayerState::GetMaxAP() const
{
	return MaxAP;
}
