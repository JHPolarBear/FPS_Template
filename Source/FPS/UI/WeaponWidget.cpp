// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WeaponWidget.h"

#include "Items/Weapons/FPSWeapon.h"

bool UWeaponWidget::BindWeapon(class AFPSWeapon* weapon)
{
	if (weapon != nullptr)
	{
		CurrentWeapon = weapon;
		weapon->OnWeaponStateChanged.AddUObject(this, &UWeaponWidget::UpdateWeaponState);

		LOG_WARNING(TEXT("Success to bind weapon"));

		return true;
	}
	else
	{
		LOG_ERROR(TEXT("Failed to bind weapon - weapon is nullptr"));
		return false;
	}
	
}

void UWeaponWidget::UpdateWeaponState()
{

}
