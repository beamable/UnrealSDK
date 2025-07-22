
#include "BeamableCore/Public/AutoGen/LocalizationQueryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULocalizationQueryLibrary::LocalizationQueryToJsonString(const ULocalizationQuery* Serializable, const bool Pretty)
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

ULocalizationQuery* ULocalizationQueryLibrary::Make(FString Id, FOptionalArrayOfString Languages, UObject* Outer)
{
	auto Serializable = NewObject<ULocalizationQuery>(Outer);
	Serializable->Id = Id;
	Serializable->Languages = Languages;
	
	return Serializable;
}

void ULocalizationQueryLibrary::Break(const ULocalizationQuery* Serializable, FString& Id, FOptionalArrayOfString& Languages)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Languages = Serializable->Languages;
	}
		
}

