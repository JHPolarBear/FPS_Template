// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonDefines.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFPSPlayerController();

	TWeakObjectPtr<class UMainInfoWidget> GetMainInfoWidget();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UMainInfoWidget> MainInfoWidgetClass;
	
private:

	UPROPERTY()
	class UMainInfoWidget* MainInfoWidget;
	
	
};
