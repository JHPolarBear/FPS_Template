// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WeaponWidget.h"
#include "Components/Image.h" 

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

void UWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ThumbnailImage = Cast<UImage>(GetWidgetFromName(TEXT("imgWeaponThumbnail")));
}

void UWeaponWidget::UpdateWeaponState()
{
	/*ConstructorHelpers::FObjectFinder<UTexture2D> TXT_THUMB(TEXT("Texture2D'/Game/Images/Thumbnails/thumbnail_default_gun.thumbnail_default_gun'"));
	if(TXT_THUMB.Succeeded())
	{
		UTexture2D* texture_ = TXT_THUMB.Object;
		ThumbnailImage->SetBrushFromTexture(texture_);
	}*/
}
