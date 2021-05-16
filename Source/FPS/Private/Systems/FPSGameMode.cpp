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

	// ���� �÷��̾� ��Ʈ�ѷ��� ���
	PlayerControllerClass = AFPSPlayerController::StaticClass();

	// ���� �÷��̾� ������Ʈ ���
	PlayerStateClass = AFPSPlayerState::StaticClass();
}
