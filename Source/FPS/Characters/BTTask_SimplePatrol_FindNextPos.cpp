// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SimplePatrol_FindNextPos.h"

#include "NavigationSystem.h"

#include "FPSController_SimplePatrol.h"

#include "FPSCharacter_SimplePatrol.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SimplePatrol_FindNextPos::UBTTask_SimplePatrol_FindNextPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_SimplePatrol_FindNextPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingCharacter = Cast<AFPSCharacter_SimplePatrol>(OwnerComp.GetAIOwner()->GetCharacter());

	if (ControllingCharacter == nullptr)
		return EBTNodeResult::Failed;

	FVector RallyPoint = FVector::ZeroVector;

	if (ControllingCharacter->GetRallyPoint_Pos(RallyPoint) == false)
		return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AFPSController_SimplePatrol::HomePosKey);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingCharacter->GetWorld());

	auto Path = NavSystem->FindPathToLocationSynchronously(ControllingCharacter->GetWorld(), Origin, RallyPoint);

	if(Path == nullptr)
	{
		LOG_ERROR(TEXT("Failed to Find path"));
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(AFPSController_SimplePatrol::NextPosKey, RallyPoint);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AFPSController_SimplePatrol::FindNextPosKey, true);

	return EBTNodeResult::Succeeded;
	
}
