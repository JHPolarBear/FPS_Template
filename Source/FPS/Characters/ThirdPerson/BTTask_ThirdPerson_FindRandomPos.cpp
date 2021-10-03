// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ThirdPerson/BTTask_ThirdPerson_FindRandomPos.h"

#include "NavigationSystem.h"

#include "FPSAIController_ThirdPerson.h"

#include "FPSCharacter_ThirdPerson.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ThirdPerson_FindRandomPos::UBTTask_ThirdPerson_FindRandomPos()
{
	NodeName = TEXT("ThirdPerson_FindRandomPos");
}

EBTNodeResult::Type UBTTask_ThirdPerson_FindRandomPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControlloingCharacter = Cast<AFPSCharacter_ThirdPerson>(OwnerComp.GetAIOwner()->GetCharacter());
	if (ControlloingCharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(OwnerComp.GetAIOwner()->GetWorld());
	if (NavSystem == nullptr)
	{
		return EBTNodeResult::Failed;
	}


	FVector crntPos = ControlloingCharacter->GetActorLocation();

	FNavLocation nextPos;


	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 1000.f, nextPos))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AFPSAIController_ThirdPerson::CrntPosKey, crntPos);

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AFPSAIController_ThirdPerson::NextPosKey, nextPos);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
