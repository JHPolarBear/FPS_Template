// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"
#include "AIController.h"
#include "FPSController_RandomMove.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AFPSController_RandomMove : public AAIController
{
	GENERATED_BODY()

public:
	AFPSController_RandomMove();

	virtual void OnPossess(APawn* InPawn) override;

public:
	static const FName CrntPosKey;
	static const FName NextPosKey;

private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;
	
};
