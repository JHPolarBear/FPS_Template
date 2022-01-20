// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ThirdPerson/BTTask_ThirdPerson_StopAttack.h"

#include "Characters/ThirdPerson/FPSCharacter_ThirdPerson.h"

UBTTask_ThirdPerson_StopAttack::UBTTask_ThirdPerson_StopAttack()
{
	NodeName = TEXT("StopAttack");
}

EBTNodeResult::Type UBTTask_ThirdPerson_StopAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AFPSCharacter_ThirdPerson* OwerCharacter = Cast<AFPSCharacter_ThirdPerson>(OwnerComp.GetAIOwner()->GetCharacter());
	if (OwerCharacter == nullptr)
		return EBTNodeResult::Failed;

	OwerCharacter->TurnOffFire();

	return EBTNodeResult::Succeeded;
}