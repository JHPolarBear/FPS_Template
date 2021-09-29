// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_ThirdPerson.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UAnimInstance_ThirdPerson : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAnimInstance_ThirdPerson();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = true))
	float CurrentSpeed;
	
};
