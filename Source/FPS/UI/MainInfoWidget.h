// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UMainInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindPlayerState(class AFPSPlayerState* NewPlayerState);

protected:
	virtual void NativeConstruct() override;

	void UpdatePlayerState();

private:

	TWeakObjectPtr<class AFPSPlayerState> CurrentPlayerState;
	
	UPROPERTY()
	class UTextBlock* PlayerName;

	UPROPERTY()
	class UProgressBar* HPBar;

	UPROPERTY()
	class UProgressBar* APBar;	
};
