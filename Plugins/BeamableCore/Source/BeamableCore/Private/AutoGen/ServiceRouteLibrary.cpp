
#include "BeamableCore/Public/AutoGen/ServiceRouteLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UServiceRouteLibrary::ServiceRouteToJsonString(const UServiceRoute* Serializable, const bool Pretty)
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

UServiceRoute* UServiceRouteLibrary::Make(FString Service, FString Endpoint, EBeamWebhookServiceType ServiceTypeStr, UObject* Outer)
{
	auto Serializable = NewObject<UServiceRoute>(Outer);
	Serializable->Service = Service;
	Serializable->Endpoint = Endpoint;
	Serializable->ServiceTypeStr = ServiceTypeStr;
	
	return Serializable;
}

void UServiceRouteLibrary::Break(const UServiceRoute* Serializable, FString& Service, FString& Endpoint, EBeamWebhookServiceType& ServiceTypeStr)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Service = Serializable->Service;
		Endpoint = Serializable->Endpoint;
		ServiceTypeStr = Serializable->ServiceTypeStr;
	}
		
}

