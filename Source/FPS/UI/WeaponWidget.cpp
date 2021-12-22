// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WeaponWidget.h"
#include "Components/Image.h" 

#include "Player/FPSCharacter.h"

#include "Items/Weapons/FPSWeapon.h"

bool UWeaponWidget::BindWeapon(class AFPSWeapon* weapon)
{
	if (weapon != nullptr)
	{
		CurrentWeapon = weapon;
		weapon->OnWeaponStateChanged.AddUObject(this, &UWeaponWidget::UpdateWeaponState);
		weapon->OnWeaponChanged.AddUObject(this, &UWeaponWidget::UpdateWeaponInfo);

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
	
}

void UWeaponWidget::UpdateWeaponInfo()
{
	auto CrntPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (CrntPlayer)
	{
		AFPSCharacter* pPlayer = Cast<AFPSCharacter>(CrntPlayer);

		if (pPlayer)
		{

			FString ThumbnailPath = TEXT("/Game/Images/Thumbnails/");
			FString ThumbnailName = pPlayer->GetWeapon()->GetThumbnailPath();

			ThumbnailPath.Append(FString::Printf(TEXT("%s"), *ThumbnailName));

			UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *ThumbnailPath));

			if (Texture)
			{
				ThumbnailImage->SetBrushFromSoftTexture(Texture);
				//LOG_WARNING(TEXT("Success to create texture"));
			}
			else
			{
				//LOG_WARNING(TEXT("Failed to create texture"));
			}
		}
	}
}
