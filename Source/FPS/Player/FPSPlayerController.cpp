// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSPlayerController.h"
#include "Player/FPSPlayerState.h"

#include "Player/FPSCharacter.h"
#include "Items/Weapons/FPSWeapon.h"

#include "UI/MainInfoWidget.h"
#include "UI/WeaponWidget.h"

AFPSPlayerController::AFPSPlayerController()
{
	static ConstructorHelpers::FClassFinder<UMainInfoWidget> UI_MAININFO_C(TEXT("/Game/UI/UI_HUD.UI_HUD_C"));
	if(UI_MAININFO_C.Succeeded())
	{
		MainInfoWidgetClass = UI_MAININFO_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UWeaponWidget> UI_WEAPON_C(TEXT("/Game/UI/UI_WEAPON.UI_WEAPON_C"));
	if (UI_WEAPON_C.Succeeded())
	{
		WeaponWidgetClass = UI_WEAPON_C.Class;
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

	WeaponWidget = CreateWidget<UWeaponWidget>(this, WeaponWidgetClass);
	WeaponWidget->AddToViewport();

	AFPSCharacter* FPSCharacter = Cast<AFPSCharacter>(GetCharacter());
	if(FPSCharacter)
	{
		AFPSWeapon* pWeapon = FPSCharacter->GetWeapon();
		if( WeaponWidget->BindWeapon(pWeapon))
		{
			pWeapon->OnWeaponStateChanged.Broadcast();
		}
	}
}
