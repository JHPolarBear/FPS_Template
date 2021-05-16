// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainInfoWidget.h"

#include "Player/FPSPlayerState.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMainInfoWidget::BindPlayerState(class AFPSPlayerState* NewPlayerState)
{
	CurrentPlayerState = NewPlayerState;
	NewPlayerState->OnPlayerStateChanged.AddUObject(this, &UMainInfoWidget::UpdatePlayerState);
}

void UMainInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtPlayerName")));

	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));

	APBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbAP")));
}

void UMainInfoWidget::UpdatePlayerState()
{
	PlayerName->SetText(FText::FromString(CurrentPlayerState->GetPlayerName()));

	HPBar->SetPercent(CurrentPlayerState->GetHPRatio());
	APBar->SetPercent(CurrentPlayerState->GetAPRatio());
}
