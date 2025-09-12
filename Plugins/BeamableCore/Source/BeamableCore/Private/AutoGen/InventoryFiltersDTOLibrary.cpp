
#include "BeamableCore/Public/AutoGen/InventoryFiltersDTOLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UInventoryFiltersDTOLibrary::InventoryFiltersDTOToJsonString(const UInventoryFiltersDTO* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UInventoryFiltersDTO* UInventoryFiltersDTOLibrary::Make(FOptionalContentTagFilter ContentTagFilter, FOptionalTimeRange CreatedAt, FOptionalTimeRange UpdatedAt, FOptionalArrayOfPropertyFilterDTO Properties, UObject* Outer)
{
	auto Serializable = NewObject<UInventoryFiltersDTO>(Outer);
	Serializable->ContentTagFilter = ContentTagFilter;
	Serializable->CreatedAt = CreatedAt;
	Serializable->UpdatedAt = UpdatedAt;
	Serializable->Properties = Properties;
	
	return Serializable;
}

void UInventoryFiltersDTOLibrary::Break(const UInventoryFiltersDTO* Serializable, FOptionalContentTagFilter& ContentTagFilter, FOptionalTimeRange& CreatedAt, FOptionalTimeRange& UpdatedAt, FOptionalArrayOfPropertyFilterDTO& Properties)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ContentTagFilter = Serializable->ContentTagFilter;
		CreatedAt = Serializable->CreatedAt;
		UpdatedAt = Serializable->UpdatedAt;
		Properties = Serializable->Properties;
	}
		
}

