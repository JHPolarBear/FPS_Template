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

	// AI Owner���� ĳ���͸� ã�´�
	auto ControllingCharacter = Cast<AFPSCharacter_ThirdPerson>(OwnerComp.GetAIOwner()->GetCharacter());

	if (ControllingCharacter == nullptr)
		return EBTNodeResult::Failed;

	FVector PatrolPoint = FVector::ZeroVector;

	// Owner character���� ���� ��ġ�� ã�´�
	if (ControllingCharacter->GetSinglePatrol_Position(PatrolPoint) == false)
		return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AFPSAIController_ThirdPerson::CrntPosKey);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingCharacter->GetWorld());

	// ���� ��ġ���� ���� ��ġ���� �׺���̼����� ���� �����ϴ��� Ȯ��
	auto Path = NavSystem->FindPathToLocationSynchronously(ControllingCharacter->GetWorld(), Origin, PatrolPoint);

	if (Path == nullptr)
	{
		LOG_ERROR(TEXT("Failed to Find path"));
		return EBTNodeResult::Failed;
	}

	// ������ġ�� �����忡 ����ϰ�, �����忡 ���� ��ġ�� ã�Ҵٰ� �˸�
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(AFPSAIController_ThirdPerson::NextPosKey, PatrolPoint);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AFPSAIController_ThirdPerson::SimplePatrol_FindPosKey, true);


	return EBTNodeResult::Succeeded;
}
