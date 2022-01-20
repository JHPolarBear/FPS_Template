// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ThirdPerson/BTTask_ThirdPerson_StartAttack.h"
#include "Characters/ThirdPerson/FPSCharacter_ThirdPerson.h"
#include "Characters/ThirdPerson/FPSAIController_ThirdPerson.h"
#include "Player/FPSCharacter.h"

UBTTask_ThirdPerson_StartAttack::UBTTask_ThirdPerson_StartAttack()
{
	NodeName = TEXT("Start Attack");
}

EBTNodeResult::Type UBTTask_ThirdPerson_StartAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AFPSCharacter_ThirdPerson* OwerCharacter = Cast<AFPSCharacter_ThirdPerson>(OwnerComp.GetAIOwner()->GetCharacter());
	if(OwerCharacter == nullptr)
		return EBTNodeResult::Failed;

	auto Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(AFPSAIController_ThirdPerson::TargetKey);
	if (Target == nullptr)
		return EBTNodeResult::Failed;

	AFPSCharacter* TPSCharacterTarget = Cast<AFPSCharacter>(Target);
	if (TPSCharacterTarget == nullptr)
		return EBTNodeResult::Failed;
	FVector TargetPos = TPSCharacterTarget->GetActorLocation();

	// Always update charachter aim
	OwerCharacter->AimTarget(TargetPos);

	// return if character already started attack
	if (OwerCharacter->GetFireHandle().IsValid())
		return EBTNodeResult::Succeeded;

	OwerCharacter->TurnOnFire();

	return EBTNodeResult::Succeeded;
}
