// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSController_SimplePatrol.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName  AFPSController_SimplePatrol::HomePosKey(TEXT("HomePos"));
const FName  AFPSController_SimplePatrol::NextPosKey(TEXT("NextPos"));
const FName  AFPSController_SimplePatrol::FindNextPosKey(TEXT("FindNextPos"));

AFPSController_SimplePatrol::AFPSController_SimplePatrol()
{
	// Find blackboard component and bind to a variable
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/SimplePatrol/BB_SimplePatrol.BB_SimplePatrol"));
	if(BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	// Find behaviortree component and bind to a variable
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/SimplePatrol/BT_SimplePatrol.BT_SimplePatrol"));
	if(BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AFPSController_SimplePatrol::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// set ai to use blackboard and behaviortree
	if(UseBlackboard(BBAsset, Blackboard))
	{
		if(!RunBehaviorTree(BTAsset))
		{
			LOG_ERROR(TEXT("Failed to run behavior tree"));
		}
	}

	// 기본 위치 세팅
	// set initial position
	Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());

	// 최소 Possess 시에는 False로 놓고 BT에서 최소에 한번 포지션 세팅을 한 후 True로 변경
	// set findnextposkey false at first, and change to true after find patrol position at the behavior tree
	Blackboard->SetValueAsBool(FindNextPosKey, false);
}