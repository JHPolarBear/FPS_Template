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

	// �⺻ ��ġ ����
	Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());

	// �ּ� Possess �ÿ��� False�� ���� BT���� �ּҿ� �ѹ� ������ ������ �� �� True�� ����
	Blackboard->SetValueAsBool(FindNextPosKey, false);
}