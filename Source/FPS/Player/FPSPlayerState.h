// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FPSPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);

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
	float GetCurrentHP() const;
	float GetHPRatio();

	void SetMaxAP(float _val);	
	float GetMaxAP() const; 
	float GetCurrentAP() const;
	float GetAPRatio();

	void DecreaseAP();
	void IncreaseAP();

	void SetRunMultiplier(float _val);
	float GetRunMultiplier();

	void SetDefaultWalkSpeed(float _val);
	float GetDefaultWalkSpeed();

	void Init();

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = true))
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = true))
	float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = true))
	float MaxAP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = true))
	float CurrentAP;

	/** Amount of AP decrease for a frame when player runs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = true))
	float DecreaseAmountAP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = true))
	float DefaultWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, meta = (AllowPrivateAccess = true))
	float RunMultiplier;
};
