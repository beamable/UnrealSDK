
#include "BeamableCore/Public/AutoGen/ItemPropertiesDeltaLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UItemPropertiesDeltaLibrary::ItemPropertiesDeltaToJsonString(const UItemPropertiesDelta* Serializable, const bool Pretty)
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

UItemPropertiesDelta* UItemPropertiesDeltaLibrary::Make(FString ContentId, int64 ItemId, FOptionalMapOfPropertyDelta Properties, UObject* Outer)
{
	auto Serializable = NewObject<UItemPropertiesDelta>(Outer);
	Serializable->ContentId = ContentId;
	Serializable->ItemId = ItemId;
	Serializable->Properties = Properties;
	
	return Serializable;
}

void UItemPropertiesDeltaLibrary::Break(const UItemPropertiesDelta* Serializable, FString& ContentId, int64& ItemId, FOptionalMapOfPropertyDelta& Properties)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ContentId = Serializable->ContentId;
		ItemId = Serializable->ItemId;
		Properties = Serializable->Properties;
	}
		
}

