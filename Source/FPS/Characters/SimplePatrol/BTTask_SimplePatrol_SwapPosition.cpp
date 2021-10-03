// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SimplePatrol_SwapPosition.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "FPSAIController_SimplePatrol.h"

#include "NavigationSystem.h"

UBTTask_SimplePatrol_SwapPosition::UBTTask_SimplePatrol_SwapPosition()
{
	NodeName = TEXT("SimplePatrol_SwapPosition");
}

EBTNodeResult::Type UBTTask_SimplePatrol_SwapPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();

	if(OwnerComp.GetBlackboardComponent() == nullptr)
		return EBTNodeResult::Failed;	

	FVector PrevNextPos= BlackBoard->GetValueAsVector(AFPSAIController_SimplePatrol::NextPosKey);
	
	FVector PrevHomePos = BlackBoard->GetValueAsVector(AFPSAIController_SimplePatrol::HomePosKey);

	BlackBoard->SetValueAsVector(AFPSAIController_SimplePatrol::NextPosKey, PrevHomePos);
	
	BlackBoard->SetValueAsVector(AFPSAIController_SimplePatrol::HomePosKey, PrevNextPos);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(OwnerComp.GetAIOwner()->GetCharacter()->GetWorld());
	if(nullptr == NavSystem)
		return EBTNodeResult::Failed;

	if(NavSystem->FindPathToLocationSynchronously(OwnerComp.GetAIOwner()->GetCharacter()->GetWorld(), PrevNextPos, PrevHomePos) == NULL)
	{
		LOG_ERROR(TEXT("Faild to findPath"));
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}