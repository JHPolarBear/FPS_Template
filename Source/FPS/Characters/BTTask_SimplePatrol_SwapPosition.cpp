// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SimplePatrol_SwapPosition.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "FPSController_SimplePatrol.h"

UBTTask_SimplePatrol_SwapPosition::UBTTask_SimplePatrol_SwapPosition()
{
	NodeName = TEXT("SimplePatrol_SwapPosition");
}

EBTNodeResult::Type UBTTask_SimplePatrol_SwapPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();

	if(OwnerComp.GetBlackboardComponent() == nullptr)
		return EBTNodeResult::Failed;	

	FVector PrevNextPos= BlackBoard->GetValueAsVector(AFPSController_SimplePatrol::NextPosKey);
	
	FVector PrevHomePos = BlackBoard->GetValueAsVector(AFPSController_SimplePatrol::HomePosKey);

	BlackBoard->SetValueAsVector(AFPSController_SimplePatrol::NextPosKey, PrevHomePos);
	
	BlackBoard->SetValueAsVector(AFPSController_SimplePatrol::HomePosKey, PrevNextPos);

	return EBTNodeResult::Succeeded;
}