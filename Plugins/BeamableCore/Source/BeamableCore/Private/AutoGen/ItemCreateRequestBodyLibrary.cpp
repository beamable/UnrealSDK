
#include "BeamableCore/Public/AutoGen/ItemCreateRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UItemCreateRequestBodyLibrary::ItemCreateRequestBodyToJsonString(const UItemCreateRequestBody* Serializable, const bool Pretty)
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

UItemCreateRequestBody* UItemCreateRequestBodyLibrary::Make(FString ContentId, TArray<UItemProperty*> Properties, UObject* Outer)
{
	auto Serializable = NewObject<UItemCreateRequestBody>(Outer);
	Serializable->ContentId = ContentId;
	Serializable->Properties = Properties;
	
	return Serializable;
}

void UItemCreateRequestBodyLibrary::Break(const UItemCreateRequestBody* Serializable, FString& ContentId, TArray<UItemProperty*>& Properties)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ContentId = Serializable->ContentId;
		Properties = Serializable->Properties;
	}
		
}

