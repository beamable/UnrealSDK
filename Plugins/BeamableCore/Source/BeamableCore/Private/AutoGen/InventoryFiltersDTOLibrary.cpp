
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

UInventoryFiltersDTO* UInventoryFiltersDTOLibrary::Make(FOptionalTimeRange UpdatedAt, FOptionalTimeRange CreatedAt, FOptionalContentTagFilter ContentTagFilter, FOptionalArrayOfString ProxyIds, FOptionalArrayOfPropertyFilterDTO PropertyFilters, UObject* Outer)
{
	auto Serializable = NewObject<UInventoryFiltersDTO>(Outer);
	Serializable->UpdatedAt = UpdatedAt;
	Serializable->CreatedAt = CreatedAt;
	Serializable->ContentTagFilter = ContentTagFilter;
	Serializable->ProxyIds = ProxyIds;
	Serializable->PropertyFilters = PropertyFilters;
	
	return Serializable;
}

void UInventoryFiltersDTOLibrary::Break(const UInventoryFiltersDTO* Serializable, FOptionalTimeRange& UpdatedAt, FOptionalTimeRange& CreatedAt, FOptionalContentTagFilter& ContentTagFilter, FOptionalArrayOfString& ProxyIds, FOptionalArrayOfPropertyFilterDTO& PropertyFilters)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		UpdatedAt = Serializable->UpdatedAt;
		CreatedAt = Serializable->CreatedAt;
		ContentTagFilter = Serializable->ContentTagFilter;
		ProxyIds = Serializable->ProxyIds;
		PropertyFilters = Serializable->PropertyFilters;
	}
		
}

