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

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void	SetIsDead(bool _val)	{IsDead = _val;}
	bool	GetIsDead()				{return IsDead;}

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool IsDead;
	
};
