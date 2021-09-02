// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"
#include "Engine/GameInstance.h"
#include "FPSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UFPSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFPSGameInstance();

public:
	struct FItemData* GetItemData(int32 _ID);

private:
	class UDataTable* FPSItemTable;
	
};
