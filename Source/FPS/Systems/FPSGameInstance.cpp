// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/FPSGameInstance.h"
#include "Systems/PlayerSystem.h"

UFPSGameInstance::UFPSGameInstance()
{
	LOG_WARNING(TEXT("Game Instance created"));

	this->GetSubsystem<UPlayerSystem>();

	// Item Table 로드
	FString ItemTablePath = TEXT("DataTable'/Game/Data/Items/ItemTable.ItemTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEMTABLE(*ItemTablePath);

	if(DT_ITEMTABLE.Succeeded())
	{
		FPSItemTable = DT_ITEMTABLE.Object;
	}

	ASSERT_CHECK(FPSItemTable->GetRowMap().Num() > 0);

 	FString CharacterLevelTablePath = TEXT("DataTable'/Game/Data/Characters/DataTable_CharacterLevel.DataTable_CharacterLevel'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CHARLEVELTABLE(*CharacterLevelTablePath);
	if(DT_CHARLEVELTABLE.Succeeded())
	{
		FPSCharacterLevelTable = DT_CHARLEVELTABLE.Object;
	}

	ASSERT_CHECK(FPSCharacterLevelTable->GetRowMap().Num() > 0);
}

// Find item data from row index
// Row Index를 ID로 쓴다
FItemData* UFPSGameInstance::GetItemData(int32 _ID)
{
	return FPSItemTable->FindRow<FItemData>(*FString::FromInt(_ID), TEXT(""));
}

// Find Character stat from level
struct FCharacterLevelData* UFPSGameInstance::GetCharacterLevelData(int32 _Level)
{
	return FPSCharacterLevelTable->FindRow<FCharacterLevelData>(*FString::FromInt(_Level), TEXT(""));
}
