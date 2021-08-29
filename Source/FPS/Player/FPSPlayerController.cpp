// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSPlayerController.h"
#include "Player/FPSPlayerState.h"

#include "UI/MainInfoWidget.h"

AFPSPlayerController::AFPSPlayerController()
{
	static ConstructorHelpers::FClassFinder<UMainInfoWidget> UI_MAININFO_C(TEXT("/Game/UI/UI_HUD.UI_HUD_C"));
	if(UI_MAININFO_C.Succeeded())
	{
		MainInfoWidgetClass = UI_MAININFO_C.Class;
	}
}

TWeakObjectPtr<class UMainInfoWidget> AFPSPlayerController::GetMainInfoWidget()
{
	return MainInfoWidget;
}

void AFPSPlayerController::BeginPlay()
{
	MainInfoWidget = CreateWidget<UMainInfoWidget>(this, MainInfoWidgetClass);
	MainInfoWidget->AddToViewport(1);

	AFPSPlayerState* FPSPlayerState = Cast<AFPSPlayerState>(PlayerState);

	if(FPSPlayerState)
	{
		MainInfoWidget->BindPlayerState(FPSPlayerState);
		FPSPlayerState->OnPlayerStateChanged.Broadcast();
	}
	else
	{
		LOG_ERROR(TEXT("Failed to bind playerstate"));
	}
}
