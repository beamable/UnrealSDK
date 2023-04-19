
#include "BeamableCore/Public/AutoGen/ServiceRouteLibrary.h"

#include "CoreMinimal.h"


FString UServiceRouteLibrary::ServiceRouteToJsonString(const UServiceRoute* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UServiceRoute* UServiceRouteLibrary::Make(FString Service, FString Endpoint, EWebhookServiceType ServiceTypeStr, UObject* Outer)
{
	auto Serializable = NewObject<UServiceRoute>(Outer);
	Serializable->Service = Service;
	Serializable->Endpoint = Endpoint;
	Serializable->ServiceTypeStr = ServiceTypeStr;
	
	return Serializable;
}

void UServiceRouteLibrary::Break(const UServiceRoute* Serializable, FString& Service, FString& Endpoint, EWebhookServiceType& ServiceTypeStr)
{
	Service = Serializable->Service;
	Endpoint = Serializable->Endpoint;
	ServiceTypeStr = Serializable->ServiceTypeStr;
		
}

