// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RandomMove/FPSController_RandomMove.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AFPSController_RandomMove::CrntPosKey(TEXT("CrntPos"));
const FName AFPSController_RandomMove::NextPosKey(TEXT("NextPos"));

AFPSController_RandomMove::AFPSController_RandomMove()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/RandomMove/BB_RanomMove.BB_RanomMove"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/RandomMove/BT_RandomMove.BT_RandomMove'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AFPSController_RandomMove::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		if (!RunBehaviorTree(BTAsset))
		{
			LOG_ERROR(TEXT("Failed to run behavior tree"));
		}
	}
}
