// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/FPSGameInstance.h"
#include "Systems/PlayerSystem.h"

UFPSGameInstance::UFPSGameInstance()
{
	LOG_WARNING(TEXT("Game Instance created"));

	this->GetSubsystem<UPlayerSystem>();

	// Item Table �ε�
	FString ItemTablePath = TEXT("DataTable'/Game/Data/ItemTable.ItemTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEMTABLE(*ItemTablePath);

	if(DT_ITEMTABLE.Succeeded())
	{
		FPSItemTable = DT_ITEMTABLE.Object;
	}
}

// Row Index�� ID�� ����
FItemData* UFPSGameInstance::GetItemData(int32 _ID)
{
	return FPSItemTable->FindRow<FItemData>(*FString::FromInt(_ID), TEXT(""));
}
