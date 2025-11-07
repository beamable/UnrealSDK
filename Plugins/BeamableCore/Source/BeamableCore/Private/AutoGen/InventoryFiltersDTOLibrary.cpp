
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

UInventoryFiltersDTO* UInventoryFiltersDTOLibrary::Make(FOptionalContentTagFilter ContentTagFilter, FOptionalTimeRange CreatedAt, FOptionalTimeRange UpdatedAt, FOptionalArrayOfPropertyFilterDTO PropertyFilters, UObject* Outer)
{
	auto Serializable = NewObject<UInventoryFiltersDTO>(Outer);
	Serializable->ContentTagFilter = ContentTagFilter;
	Serializable->CreatedAt = CreatedAt;
	Serializable->UpdatedAt = UpdatedAt;
	Serializable->PropertyFilters = PropertyFilters;
	
	return Serializable;
}

void UInventoryFiltersDTOLibrary::Break(const UInventoryFiltersDTO* Serializable, FOptionalContentTagFilter& ContentTagFilter, FOptionalTimeRange& CreatedAt, FOptionalTimeRange& UpdatedAt, FOptionalArrayOfPropertyFilterDTO& PropertyFilters)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ContentTagFilter = Serializable->ContentTagFilter;
		CreatedAt = Serializable->CreatedAt;
		UpdatedAt = Serializable->UpdatedAt;
		PropertyFilters = Serializable->PropertyFilters;
	}
		
}

