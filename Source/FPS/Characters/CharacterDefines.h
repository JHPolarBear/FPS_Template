// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"

UENUM()
enum class EPatrolType
{
	PATROL_NONE,

	PATROL_STILL,			// stay on position
	PATROL_SINGLEPATROL,	// patrol between two points
	PATROL_RANDOMMOVE,		// randomly move on the nav mesh 

	PATROL_MAX,
};
