// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ThirdPerson/BTTask_ThirdPerson_FindPatrolPos.h"

#include "NavigationSystem.h"

#include "FPSCharacter_ThirdPerson.h"
#include "FPSAIController_ThirdPerson.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ThirdPerson_FindPatrolPos::UBTTask_ThirdPerson_FindPatrolPos()
{
	NodeName = TEXT("ThirdPerson_FindPatrolPos");
}

EBTNodeResult::Type UBTTask_ThirdPerson_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	// AI Owner에서 캐릭터를 찾는다
	auto ControllingCharacter = Cast<AFPSCharacter_ThirdPerson>(OwnerComp.GetAIOwner()->GetCharacter());

	if (ControllingCharacter == nullptr)
		return EBTNodeResult::Failed;

	FVector PatrolPoint = FVector::ZeroVector;

	// Owner character에서 순찰 위치를 찾는다
	if (ControllingCharacter->GetSinglePatrol_Position(PatrolPoint) == false)
		return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AFPSAIController_ThirdPerson::CrntPosKey);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingCharacter->GetWorld());

	// 현재 위치에서 순찰 위치까지 네비게이션으로 길이 존재하는지 확인
	auto Path = NavSystem->FindPathToLocationSynchronously(ControllingCharacter->GetWorld(), Origin, PatrolPoint);

	if (Path == nullptr)
	{
		LOG_ERROR(TEXT("Failed to Find path"));
		return EBTNodeResult::Failed;
	}

	// 순찰위치를 블랙보드에 등록하고, 블랙보드에 순찰 위치를 찾았다고 알림
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(AFPSAIController_ThirdPerson::NextPosKey, PatrolPoint);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AFPSAIController_ThirdPerson::SimplePatrol_FindPosKey, true);


	return EBTNodeResult::Succeeded;
}
