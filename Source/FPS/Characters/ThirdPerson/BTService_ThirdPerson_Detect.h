// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"
#include "BehaviorTree/BTService.h"
#include "BTService_ThirdPerson_Detect.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UBTService_ThirdPerson_Detect : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_ThirdPerson_Detect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	
};
