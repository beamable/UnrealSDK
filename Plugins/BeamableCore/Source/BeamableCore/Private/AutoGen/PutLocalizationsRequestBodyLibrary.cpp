
#include "BeamableCore/Public/AutoGen/PutLocalizationsRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UPutLocalizationsRequestBodyLibrary::PutLocalizationsRequestBodyToJsonString(const UPutLocalizationsRequestBody* Serializable, const bool Pretty)
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

UPutLocalizationsRequestBody* UPutLocalizationsRequestBodyLibrary::Make(TMap<FString, FArrayOfLocalizedValue> Localizations, UObject* Outer)
{
	auto Serializable = NewObject<UPutLocalizationsRequestBody>(Outer);
	Serializable->Localizations = Localizations;
	
	return Serializable;
}

void UPutLocalizationsRequestBodyLibrary::Break(const UPutLocalizationsRequestBody* Serializable, TMap<FString, FArrayOfLocalizedValue>& Localizations)
{
	Localizations = Serializable->Localizations;
		
}

