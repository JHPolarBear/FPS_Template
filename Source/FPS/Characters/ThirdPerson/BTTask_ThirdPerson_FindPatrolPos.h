// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ThirdPerson_FindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UBTTask_ThirdPerson_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ThirdPerson_FindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
