
#include "BeamableCore/Public/AutoGen/SupportedFederationsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USupportedFederationsResponseLibrary::SupportedFederationsResponseToJsonString(const USupportedFederationsResponse* Serializable, const bool Pretty)
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

USupportedFederationsResponse* USupportedFederationsResponseLibrary::Make(TArray<USupportedFederationRegistration*> Registrations, UObject* Outer)
{
	auto Serializable = NewObject<USupportedFederationsResponse>(Outer);
	Serializable->Registrations = Registrations;
	
	return Serializable;
}

void USupportedFederationsResponseLibrary::Break(const USupportedFederationsResponse* Serializable, TArray<USupportedFederationRegistration*>& Registrations)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Registrations = Serializable->Registrations;
	}
		
}

