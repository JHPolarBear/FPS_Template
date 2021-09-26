// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/RandomMove/BTTask_RandomMove_FindNextPos.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AIController.h"

#include "FPSCharacter_RandomMove.h"
#include "FPSController_RandomMove.h"

UBTTask_RandomMove_FindNextPos::UBTTask_RandomMove_FindNextPos()
{
	NodeName = TEXT("RandomMove_FindNextPos");
}

EBTNodeResult::Type UBTTask_RandomMove_FindNextPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControlloingCharacter = Cast<AFPSCharacter_RandomMove>(OwnerComp.GetAIOwner()->GetCharacter());
	if(ControlloingCharacter == nullptr)
	{
		//LOG_ERROR(TEXT("Faild to find controlling character"));
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(OwnerComp.GetAIOwner()->GetWorld());
	if (NavSystem == nullptr)
	{
		//LOG_ERROR(TEXT("Faild to find navigation system"));
		return EBTNodeResult::Failed;
	}

	
	FVector crntPos = ControlloingCharacter->GetActorLocation();

	FNavLocation nextPos;


	if(NavSystem->GetRandomPointInNavigableRadius(crntPos, 500.f, nextPos))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AFPSController_RandomMove::CrntPosKey, crntPos);

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AFPSController_RandomMove::NextPosKey, nextPos);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

