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
	/** ���� �÷��̾��� �÷��̾� ������Ʈ - �÷��̾� ������Ʈ�� ����� ĳ������ �ɷ�ġ�� UI�� ���ε��ϴµ� ���   */
	TWeakObjectPtr<class AFPSPlayerState> CurrentPlayerState;
	
	/** Player ID(NickName) */
	UPROPERTY()
	class UTextBlock* PlayerName;

	/** Player remain HP */
	UPROPERTY()
	class UProgressBar* HPBar;

	/** Player remain AP(Dash Point): Character can dash while AP remains */
	/** �÷��̾� AP : AP�� ������������ �÷��̾� �뽬(�޸���)�� ���� */
	UPROPERTY()
	class UProgressBar* APBar;	
};
