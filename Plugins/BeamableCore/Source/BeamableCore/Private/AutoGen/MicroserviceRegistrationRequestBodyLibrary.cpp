
#include "BeamableCore/Public/AutoGen/MicroserviceRegistrationRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMicroserviceRegistrationRequestBodyLibrary::MicroserviceRegistrationRequestBodyToJsonString(const UMicroserviceRegistrationRequestBody* Serializable, const bool Pretty)
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

UMicroserviceRegistrationRequestBody* UMicroserviceRegistrationRequestBodyLibrary::Make(FString ServiceName, FOptionalBool bTrafficFilterEnabled, FOptionalString RoutingKey, FOptionalArrayOfSupportedFederation Federation, UObject* Outer)
{
	auto Serializable = NewObject<UMicroserviceRegistrationRequestBody>(Outer);
	Serializable->ServiceName = ServiceName;
	Serializable->bTrafficFilterEnabled = bTrafficFilterEnabled;
	Serializable->RoutingKey = RoutingKey;
	Serializable->Federation = Federation;
	
	return Serializable;
}

void UMicroserviceRegistrationRequestBodyLibrary::Break(const UMicroserviceRegistrationRequestBody* Serializable, FString& ServiceName, FOptionalBool& bTrafficFilterEnabled, FOptionalString& RoutingKey, FOptionalArrayOfSupportedFederation& Federation)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ServiceName = Serializable->ServiceName;
		bTrafficFilterEnabled = Serializable->bTrafficFilterEnabled;
		RoutingKey = Serializable->RoutingKey;
		Federation = Serializable->Federation;
	}
		
}

