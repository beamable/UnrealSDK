
#include "BeamableCore/Public/AutoGen/ItemUpdateRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UItemUpdateRequestBodyLibrary::ItemUpdateRequestBodyToJsonString(const UItemUpdateRequestBody* Serializable, const bool Pretty)
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

UItemUpdateRequestBody* UItemUpdateRequestBodyLibrary::Make(FString ContentId, int64 Id, TArray<UItemProperty*> Properties, UObject* Outer)
{
	auto Serializable = NewObject<UItemUpdateRequestBody>(Outer);
	Serializable->ContentId = ContentId;
	Serializable->Id = Id;
	Serializable->Properties = Properties;
	
	return Serializable;
}

void UItemUpdateRequestBodyLibrary::Break(const UItemUpdateRequestBody* Serializable, FString& ContentId, int64& Id, TArray<UItemProperty*>& Properties)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ContentId = Serializable->ContentId;
		Id = Serializable->Id;
		Properties = Serializable->Properties;
	}
		
}

