// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"
#include "UObject/NoExportTypes.h"
#include "ItemDefines.generated.h"

// Enum for item type
UENUM()
enum class EItemTypes
{
	ITEM_NONE,

	ITEM_RIFLE,
	ITEM_HANDGUN,
	ITEM_DAGGER,

	ITEM_MAX,
};

/**
 * 
 */
UCLASS()
class FPS_API UItemDefines : public UObject
{
	GENERATED_BODY()
	
};
