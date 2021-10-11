// Fill out your copyright notice in the Description page of Project Settings.
/************************************************************************/
/* Desc:	Stat component for character                                */
/*			Contains HP, AP Point	                                    */
/************************************************************************/

#pragma once

#include "CommonDefines.h"
#include "Components/ActorComponent.h"
#include "StatComponent_ThirdPerson.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UStatComponent_ThirdPerson : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent_ThirdPerson();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	virtual void InitializeComponent() override;

public:
	void Init();
	
	// Set level for character stat
	// @Params
	// _NewLevel : level value
	// _RefreshCurrentStat : whether to refresh current stat after setting new level information 
	void SetNewLevel(int32 _NewLevel, bool _RefreshCurrentStat = false);

	float GetMaxHP() const;
	float GetCurrentHP() const;
	float GetHPRatio();

	float GetMaxAP() const;
	float GetCurrentAP() const;
	float GetAPRatio();

	void DecreaseAP();
	void IncreaseAP();

	void SetRunMultiplier(float _val);
	float GetRunMultiplier();

	void SetDefaultWalkSpeed(float _val);
	float GetDefaultWalkSpeed();

private:
	FCharacterLevelData* CurrentLevelData = nullptr;

	/** Character's current level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = true))
	float Level;

	/** Character's current hp */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = true))
	float CurrentHP;

	/** Character's current AP */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = true))
	float CurrentAP;

	/** Amount of AP decrease for a frame when player runs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = true))
	float DecreaseAmountAP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = true))
	float DefaultWalkSpeed;

	/** Dash parameter */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = true))
	float RunMultiplier;
};