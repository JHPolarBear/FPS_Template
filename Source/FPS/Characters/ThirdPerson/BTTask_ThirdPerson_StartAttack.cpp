// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ThirdPerson/BTTask_ThirdPerson_StartAttack.h"
#include "Characters/ThirdPerson/FPSCharacter_ThirdPerson.h"

UBTTask_ThirdPerson_StartAttack::UBTTask_ThirdPerson_StartAttack()
{
	NodeName = TEXT("Start Attack");
}

EBTNodeResult::Type UBTTask_ThirdPerson_StartAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	 AFPSCharacter_ThirdPerson* OwerCharacter = Cast<AFPSCharacter_ThirdPerson>(OwnerComp.GetAIOwner()->GetCharacter());
	 if(OwerCharacter == nullptr)
		return EBTNodeResult::Failed;

	OwerCharacter->TurnOnFire();

	return EBTNodeResult::Succeeded;
}
