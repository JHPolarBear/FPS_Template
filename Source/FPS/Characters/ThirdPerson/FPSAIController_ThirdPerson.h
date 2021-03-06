// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"
#include "AIController.h"
#include "FPSAIController_ThirdPerson.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AFPSAIController_ThirdPerson : public AAIController
{
	GENERATED_BODY()

public:
	AFPSAIController_ThirdPerson();

	virtual void OnPossess(APawn* aPawn) override;


/**** Variables  ****/
private:

	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Perception, meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Sight* SightSenseConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Perception, meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Hearing* HearingSenseConfig;

/**** AI Components ****/
public:

	/************************************************************************/
	/** Commonly use */

	// Current and next target position
	static const FName CrntPosKey;
	static const FName NextPosKey;

	// Target Key
	static const FName TargetKey;
	// Can AI attack the target
	static const FName IsAttackableKey;

	// NPC's patrol type
	static const FName PatrolTypeKey;

	/************************************************************************/
	/** Simple Patrol */

	// flag whether patrol position is set
	static const FName SimplePatrol_FindPosKey;

	/************************************************************************/
	
};
