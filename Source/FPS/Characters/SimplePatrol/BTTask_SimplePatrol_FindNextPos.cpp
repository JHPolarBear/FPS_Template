// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SimplePatrol_FindNextPos.h"

#include "NavigationSystem.h"

#include "FPSController_SimplePatrol.h"

#include "FPSCharacter_SimplePatrol.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SimplePatrol_FindNextPos::UBTTask_SimplePatrol_FindNextPos()
{
	NodeName = TEXT("SimplePatrol_FindPatrolPos");
}

EBTNodeResult::Type UBTTask_SimplePatrol_FindNextPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	// AI Owner에서 캐릭터를 찾는다
	auto ControllingCharacter = Cast<AFPSCharacter_SimplePatrol>(OwnerComp.GetAIOwner()->GetCharacter());

	if (ControllingCharacter == nullptr)
		return EBTNodeResult::Failed;

	FVector RallyPoint = FVector::ZeroVector;

	// Owner character에서 순찰 위치를 찾는다
	if (ControllingCharacter->GetRallyPoint_Pos(RallyPoint) == false)
		return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AFPSController_SimplePatrol::HomePosKey);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingCharacter->GetWorld());

	// 현재 위치에서 순찰 위치까지 네비게이션으로 길이 존재하는지 확인
	auto Path = NavSystem->FindPathToLocationSynchronously(ControllingCharacter->GetWorld(), Origin, RallyPoint);

	if(Path == nullptr)
	{
		LOG_ERROR(TEXT("Failed to Find path"));
		return EBTNodeResult::Failed;
	}

	// 순찰위치를 블랙보드에 등록하고, 블랙보드에 순찰 위치를 찾았다고 알림
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(AFPSController_SimplePatrol::NextPosKey, RallyPoint);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AFPSController_SimplePatrol::FindNextPosKey, true);
	

	return EBTNodeResult::Succeeded;
	
}
