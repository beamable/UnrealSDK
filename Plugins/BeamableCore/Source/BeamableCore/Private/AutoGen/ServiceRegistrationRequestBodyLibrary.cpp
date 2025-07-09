
#include "BeamableCore/Public/AutoGen/ServiceRegistrationRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UServiceRegistrationRequestBodyLibrary::ServiceRegistrationRequestBodyToJsonString(const UServiceRegistrationRequestBody* Serializable, const bool Pretty)
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

UServiceRegistrationRequestBody* UServiceRegistrationRequestBodyLibrary::Make(FOptionalString RoutingKey, FOptionalBool bTrafficFilterEnabled, FOptionalArrayOfSupportedFederation Federation, UObject* Outer)
{
	auto Serializable = NewObject<UServiceRegistrationRequestBody>(Outer);
	Serializable->RoutingKey = RoutingKey;
	Serializable->bTrafficFilterEnabled = bTrafficFilterEnabled;
	Serializable->Federation = Federation;
	
	return Serializable;
}

void UServiceRegistrationRequestBodyLibrary::Break(const UServiceRegistrationRequestBody* Serializable, FOptionalString& RoutingKey, FOptionalBool& bTrafficFilterEnabled, FOptionalArrayOfSupportedFederation& Federation)
{
	RoutingKey = Serializable->RoutingKey;
	bTrafficFilterEnabled = Serializable->bTrafficFilterEnabled;
	Federation = Serializable->Federation;
		
}

