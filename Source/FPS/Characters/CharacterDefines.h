// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"
#include "Engine/DataTable.h"

#include "CharacterDefines.generated.h"

UENUM()
enum class EPatrolType
{
	PATROL_NONE,

	PATROL_STILL,			// stay on position
	PATROL_SINGLEPATROL,	// patrol between two points
	PATROL_RANDOMMOVE,		// randomly move on the nav mesh 

	PATROL_MAX,
};

// Character's stat
USTRUCT(BlueprintType)
struct FCharacterLevelData : public FTableRowBase
{
	GENERATED_BODY()

public:

	FCharacterLevelData(): Level(0), MaxHP(0), MaxAP(0){}

	/** Level  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	int32 Level;

	/** HP point */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHP;

	/** Action Point: Points indicating how long the character can dash */
	/** Action Point: 캐릭터가 대시할 수 있는 시간을 나타내는 포인트 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxAP;
};
