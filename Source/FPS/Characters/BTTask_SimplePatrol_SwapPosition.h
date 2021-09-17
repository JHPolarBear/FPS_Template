// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SimplePatrol_SwapPosition.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UBTTask_SimplePatrol_SwapPosition : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SimplePatrol_SwapPosition();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
