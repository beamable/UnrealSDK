
#include "BeamableCore/Public/AutoGen/DeleteLocalizationRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UDeleteLocalizationRequestBodyLibrary::DeleteLocalizationRequestBodyToJsonString(const UDeleteLocalizationRequestBody* Serializable, const bool Pretty)
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

UDeleteLocalizationRequestBody* UDeleteLocalizationRequestBodyLibrary::Make(TArray<ULocalizationQuery*> Localizations, UObject* Outer)
{
	auto Serializable = NewObject<UDeleteLocalizationRequestBody>(Outer);
	Serializable->Localizations = Localizations;
	
	return Serializable;
}

void UDeleteLocalizationRequestBodyLibrary::Break(const UDeleteLocalizationRequestBody* Serializable, TArray<ULocalizationQuery*>& Localizations)
{
	Localizations = Serializable->Localizations;
		
}

