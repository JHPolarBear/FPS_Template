// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ThirdPerson/FPSAIController_ThirdPerson.h"

#include "FPSCharacter_ThirdPerson.h"

#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

const FName AFPSAIController_ThirdPerson::CrntPosKey(TEXT("CrntPos"));
const FName AFPSAIController_ThirdPerson::NextPosKey(TEXT("NextPos"));

const FName AFPSAIController_ThirdPerson::PatrolTypeKey(TEXT("PatrolType"));

const FName AFPSAIController_ThirdPerson::SimplePatrol_FindPosKey(TEXT("SimplePatrol_FindPos"));

AFPSAIController_ThirdPerson::AFPSAIController_ThirdPerson()
{
	// Find blackboard component and bind to a variable
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/ThirdPerson/BB_ThirdPerson_AI.BB_ThirdPerson_AI"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	// Find behaviortree component and bind to a variable
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/ThirdPerson/BT_ThirdPerson_AI.BT_ThirdPerson_AI"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AFPSAIController_ThirdPerson::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	auto crntCharacter = Cast<AFPSCharacter_ThirdPerson>(GetCharacter());

	ASSERT_CHECK(crntCharacter != nullptr)

	EPatrolType PatrolType = crntCharacter->GetPatrolType();

	// set ai to use blackboard and behaviortree
	if (UseBlackboard(BBAsset, Blackboard))
	{
		if (!RunBehaviorTree(BTAsset))
		{
			LOG_ERROR(TEXT("Failed to run behavior tree"));
		}
	}

	// 기본 위치 세팅
	// set initial position
	Blackboard->SetValueAsVector(CrntPosKey, aPawn->GetActorLocation());

	// set initial patrol type (Still)
	Blackboard->SetValueAsEnum(PatrolTypeKey, (uint8)PatrolType);

	// set find pos key flag to false
	Blackboard->SetValueAsBool(SimplePatrol_FindPosKey, false);
}
