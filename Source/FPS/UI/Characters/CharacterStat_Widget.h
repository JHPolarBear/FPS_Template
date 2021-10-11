// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"
#include "Blueprint/UserWidget.h"
#include "CharacterStat_Widget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UCharacterStat_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	void BindCharacterStat(class UStatComponent_ThirdPerson* _NewCharacterStat);

	void UpdateCharcterStat();

private:
	TWeakObjectPtr<class UStatComponent_ThirdPerson> CurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* HPProgressBar;

	UPROPERTY()
	class UProgressBar* APProgressBar;
	
};
