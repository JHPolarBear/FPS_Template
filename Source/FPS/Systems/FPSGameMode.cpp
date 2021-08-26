// Copyright Epic Games, Inc. All Rights Reserved.

#include "Systems/FPSGameMode.h"
#include "UI/FPSHUD.h"
#include "Player/FPSCharacter.h"
#include "Player/FPSPlayerController.h"
#include "Player/FPSPlayerState.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;
	DefaultPawnClass = AFPSCharacter::StaticClass();

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	// 전용 플레이어 컨트롤러를 사용
	PlayerControllerClass = AFPSPlayerController::StaticClass();

	// 전용 플레이어 스테이트 사용
	PlayerStateClass = AFPSPlayerState::StaticClass();
}
