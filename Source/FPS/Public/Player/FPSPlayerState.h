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

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccessOnly = true))
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccessOnly = true))
	float MaxAP;
	
};
