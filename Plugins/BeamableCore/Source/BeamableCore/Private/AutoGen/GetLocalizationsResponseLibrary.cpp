
#include "BeamableCore/Public/AutoGen/GetLocalizationsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetLocalizationsResponseLibrary::GetLocalizationsResponseToJsonString(const UGetLocalizationsResponse* Serializable, const bool Pretty)
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

UGetLocalizationsResponse* UGetLocalizationsResponseLibrary::Make(TMap<FString, FArrayOfLocalizedValue> Localizations, UObject* Outer)
{
	auto Serializable = NewObject<UGetLocalizationsResponse>(Outer);
	Serializable->Localizations = Localizations;
	
	return Serializable;
}

void UGetLocalizationsResponseLibrary::Break(const UGetLocalizationsResponse* Serializable, TMap<FString, FArrayOfLocalizedValue>& Localizations)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Localizations = Serializable->Localizations;
	}
		
}

