// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(FPSGame, Log, All);

#define LOG_CALLINFO (FString(__FUNCTION__) + TEXT("[") + FString::FromInt(__LINE__) + TEXT("]"))
#define LOG_WARNING(format, ...) UE_LOG(FPSGame, Warning, TEXT("%s %s"), *LOG_CALLINFO, *FString::Printf(format, ##__VA_ARGS__)) 
#define LOG_ERROR(format, ...) UE_LOG(FPSGame, Error, TEXT("%s %s"), *LOG_CALLINFO, *FString::Printf(format, ##__VA_ARGS__)) 