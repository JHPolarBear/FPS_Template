// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerSystem.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UPlayerSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPlayerSystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
};
