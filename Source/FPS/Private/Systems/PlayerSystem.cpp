// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/PlayerSystem.h"

UPlayerSystem::UPlayerSystem()
{
	LOG_WARNING(TEXT("PlayerSystem Created"));
}	

void UPlayerSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	LOG_WARNING(TEXT("PlayerSystem Initialized"));
}

void UPlayerSystem::Deinitialize()
{
	LOG_WARNING(TEXT("PlayerSystem Deinitialized"));
}
