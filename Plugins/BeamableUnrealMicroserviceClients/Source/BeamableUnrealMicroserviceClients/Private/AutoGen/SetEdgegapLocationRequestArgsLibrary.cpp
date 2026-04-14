
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SetEdgegapLocationRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USetEdgegapLocationRequestArgsLibrary::SetEdgegapLocationRequestArgsToJsonString(const USetEdgegapLocationRequestArgs* Serializable, const bool Pretty)
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

USetEdgegapLocationRequestArgs* USetEdgegapLocationRequestArgsLibrary::Make(float Latitude, float Longitude, UObject* Outer)
{
	auto Serializable = NewObject<USetEdgegapLocationRequestArgs>(Outer);
	Serializable->Latitude = Latitude;
	Serializable->Longitude = Longitude;
	
	return Serializable;
}

void USetEdgegapLocationRequestArgsLibrary::Break(const USetEdgegapLocationRequestArgs* Serializable, float& Latitude, float& Longitude)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Latitude = Serializable->Latitude;
		Longitude = Serializable->Longitude;
	}
		
}

