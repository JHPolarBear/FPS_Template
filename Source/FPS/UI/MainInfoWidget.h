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

	/** Pointer of current playerstate : used to bind player ability declared in playerstate to UI using delegate */
	/** 현재 플레이어의 플레이어 스테이트 - 플레이어 스테이트에 선언된 캐릭터의 능력치를 UI에 바인딩하는데 사용   */
	TWeakObjectPtr<class AFPSPlayerState> CurrentPlayerState;
	
	/** Player ID(NickName) */
	UPROPERTY()
	class UTextBlock* PlayerName;

	/** Player remain HP */
	UPROPERTY()
	class UProgressBar* HPBar;

	/** Player remain AP(Dash Point): Character can dash while AP remains */
	/** 플레이어 AP : AP가 남아있을때만 플레이어 대쉬(달리기)가 가능 */
	UPROPERTY()
	class UProgressBar* APBar;	
};
