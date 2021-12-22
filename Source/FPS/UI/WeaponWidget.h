// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UWeaponWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	bool BindWeapon(class AFPSWeapon* weapon);

	virtual void NativeConstruct() override;

	void UpdateWeaponState();

	void UpdateWeaponInfo();

private:
	TWeakObjectPtr<class AFPSWeapon> CurrentWeapon;

	class UImage* ThumbnailImage = nullptr;
};
