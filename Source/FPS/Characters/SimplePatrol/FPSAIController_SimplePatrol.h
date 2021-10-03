// Fill out your copyright notice in the Description page of Project Settings.
/**
 *  This is a simple player controller of character that patrols between two points
 */

#pragma once

#include "CommonDefines.h"
#include "AIController.h"
#include "FPSAIController_SimplePatrol.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AFPSAIController_SimplePatrol : public AAIController
{
	GENERATED_BODY()

public:
	AFPSAIController_SimplePatrol();

	virtual void OnPossess(APawn* InPawn) override;

public:
	// The name of a vector value in a blackboard (Current player position)
	static const FName HomePosKey;

	// The name of a vector value in a blackboard (Position to move)
	static const FName NextPosKey;

	// The name of a bool value in a blackboard that checks if the owner character has set a patrol position
	static const FName FindNextPosKey;
	

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
