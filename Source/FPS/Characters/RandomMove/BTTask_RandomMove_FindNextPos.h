// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RandomMove_FindNextPos.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UBTTask_RandomMove_FindNextPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_RandomMove_FindNextPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
