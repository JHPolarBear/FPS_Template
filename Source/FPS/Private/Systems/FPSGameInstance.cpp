// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/FPSGameInstance.h"
#include "Systems/PlayerSystem.h"

UFPSGameInstance::UFPSGameInstance()
{
	LOG_WARNING(TEXT("Game Instance created"));

	this->GetSubsystem<UPlayerSystem>();
}
