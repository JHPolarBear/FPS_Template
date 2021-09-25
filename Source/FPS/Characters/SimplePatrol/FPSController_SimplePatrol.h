// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"
#include "AIController.h"
#include "FPSController_SimplePatrol.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AFPSController_SimplePatrol : public AAIController
{
	GENERATED_BODY()

public:
	AFPSController_SimplePatrol();

	virtual void OnPossess(APawn* InPawn) override;

public:
	static const FName HomePosKey;
	static const FName NextPosKey;

	static const FName FindNextPosKey;
	

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
