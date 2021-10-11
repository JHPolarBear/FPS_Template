// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Characters/CharacterStat_Widget.h"

#include "Characters/ThirdPerson/StatComponent_ThirdPerson.h"

#include "Components/ProgressBar.h"

void UCharacterStat_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("NPC_PB_HPBar")));
	ASSERT_CHECK(HPProgressBar != nullptr);

	APProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("NPC_PB_APBar")));
	ASSERT_CHECK(APProgressBar != nullptr);

	UpdateCharcterStat();
}

void UCharacterStat_Widget::BindCharacterStat(class UStatComponent_ThirdPerson* _NewCharacterStat)
{
	ASSERT_CHECK(_NewCharacterStat != nullptr);

	CurrentCharacterStat = _NewCharacterStat;
	_NewCharacterStat->OnCharacterStatChanged.AddUObject(this, &UCharacterStat_Widget::UpdateCharcterStat);

}

void UCharacterStat_Widget::UpdateCharcterStat()
{
	if(CurrentCharacterStat->IsValidLowLevel())
	{
		if(HPProgressBar!= nullptr)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}

		if(APProgressBar != nullptr)
		{
			APProgressBar->SetPercent(CurrentCharacterStat->GetAPRatio());
		}
	}
}

