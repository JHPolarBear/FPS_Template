// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"

#include "Engine/DataTable.h"

#include "UObject/NoExportTypes.h"
#include "ItemDefines.generated.h"

#define _ITME_THUMBNAIL_FOLDER "/Game/Images/Thumbnails/"

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

// Item ¼Ó¼º
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:

	FItemData() : Type(0), Name(TEXT("")), FireRate(1.f), DamageValue(1.f), IsProjectileBounce(false), ThumbnailPath(TEXT("")) {}

	// Weapon ID
	// use datatable index

	// Weapon Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Type;

	// Weapon English name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Name;

	/** Weapon Fire Rate */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float DamageValue;

	/** can the projectile from weapon can be bounce */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool IsProjectileBounce;

	// Weapon Thumbnail file name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ThumbnailPath;

};

/**
 * 
 */
UCLASS()
class FPS_API UItemDefines : public UObject
{
	GENERATED_BODY()
	
};
