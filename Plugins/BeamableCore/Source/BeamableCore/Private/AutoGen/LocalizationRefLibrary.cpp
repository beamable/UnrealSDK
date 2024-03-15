
#include "BeamableCore/Public/AutoGen/LocalizationRefLibrary.h"

#include "CoreMinimal.h"


FString ULocalizationRefLibrary::LocalizationRefToJsonString(const ULocalizationRef* Serializable, const bool Pretty)
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

ULocalizationRef* ULocalizationRefLibrary::Make(bool bEmpty, FString LocalizationId, FOptionalString DefaultValue, UObject* Outer)
{
	auto Serializable = NewObject<ULocalizationRef>(Outer);
	Serializable->bEmpty = bEmpty;
	Serializable->LocalizationId = LocalizationId;
	Serializable->DefaultValue = DefaultValue;
	
	return Serializable;
}

void ULocalizationRefLibrary::Break(const ULocalizationRef* Serializable, bool& bEmpty, FString& LocalizationId, FOptionalString& DefaultValue)
{
	bEmpty = Serializable->bEmpty;
	LocalizationId = Serializable->LocalizationId;
	DefaultValue = Serializable->DefaultValue;
		
}

