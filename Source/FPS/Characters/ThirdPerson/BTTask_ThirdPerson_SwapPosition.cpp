// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ThirdPerson/BTTask_ThirdPerson_SwapPosition.h"

#include "NavigationSystem.h"

#include "FPSCharacter_ThirdPerson.h"
#include "FPSAIController_ThirdPerson.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ThirdPerson_SwapPosition::UBTTask_ThirdPerson_SwapPosition()
{
	NodeName = TEXT("SimplePatrol_SwapPosition");
}

EBTNodeResult::Type UBTTask_ThirdPerson_SwapPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();

	if (OwnerComp.GetBlackboardComponent() == nullptr)
		return EBTNodeResult::Failed;

	FVector PrevNextPos = BlackBoard->GetValueAsVector(AFPSAIController_ThirdPerson::NextPosKey);

	FVector PrevCrntPos = BlackBoard->GetValueAsVector(AFPSAIController_ThirdPerson::CrntPosKey);

	BlackBoard->SetValueAsVector(AFPSAIController_ThirdPerson::NextPosKey, PrevCrntPos);

	BlackBoard->SetValueAsVector(AFPSAIController_ThirdPerson::CrntPosKey, PrevNextPos);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(OwnerComp.GetAIOwner()->GetCharacter()->GetWorld());
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed;

	if (NavSystem->FindPathToLocationSynchronously(OwnerComp.GetAIOwner()->GetCharacter()->GetWorld(), PrevNextPos, PrevCrntPos) == NULL)
	{
		LOG_ERROR(TEXT("Faild to findPath"));
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
