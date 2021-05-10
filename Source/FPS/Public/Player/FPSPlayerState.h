// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FPSPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AFPSPlayerState : public APlayerState
{
	GENERATED_BODY()

	//플레이어 명은 APlayerState가 가지고 있다.

public:
	AFPSPlayerState();

	void SetMaxHP(float _val);
	float GetMaxHP() const; 

	void SetMaxAP(float _val);
	float GetMaxAP() const; 

	void Init();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = true))
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = true))
	float MaxAP;
	
};
