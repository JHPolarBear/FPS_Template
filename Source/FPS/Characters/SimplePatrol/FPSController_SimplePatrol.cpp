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
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/SimplePatrol/BB_SimplePatrol.BB_SimplePatrol"));
	if(BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/SimplePatrol/BT_SimplePatrol.BT_SimplePatrol"));
	if(BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AFPSController_SimplePatrol::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(UseBlackboard(BBAsset, Blackboard))
	{
		if(!RunBehaviorTree(BTAsset))
		{
			LOG_ERROR(TEXT("Failed to run behavior tree"));
		}
	}

	// 기본 위치 세팅
	Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());

	// 최소 Possess 시에는 False로 놓고 BT에서 최소에 한번 포지션 세팅을 한 후 True로 변경
	Blackboard->SetValueAsBool(FindNextPosKey, false);
}