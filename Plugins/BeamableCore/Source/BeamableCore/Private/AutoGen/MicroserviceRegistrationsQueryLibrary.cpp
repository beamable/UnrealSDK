
#include "BeamableCore/Public/AutoGen/MicroserviceRegistrationsQueryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMicroserviceRegistrationsQueryLibrary::MicroserviceRegistrationsQueryToJsonString(const UMicroserviceRegistrationsQuery* Serializable, const bool Pretty)
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

UMicroserviceRegistrationsQuery* UMicroserviceRegistrationsQueryLibrary::Make(FOptionalBool bLocalOnly, FOptionalString ServiceName, FOptionalString RoutingKey, FOptionalSupportedFederation Federation, UObject* Outer)
{
	auto Serializable = NewObject<UMicroserviceRegistrationsQuery>(Outer);
	Serializable->bLocalOnly = bLocalOnly;
	Serializable->ServiceName = ServiceName;
	Serializable->RoutingKey = RoutingKey;
	Serializable->Federation = Federation;
	
	return Serializable;
}

void UMicroserviceRegistrationsQueryLibrary::Break(const UMicroserviceRegistrationsQuery* Serializable, FOptionalBool& bLocalOnly, FOptionalString& ServiceName, FOptionalString& RoutingKey, FOptionalSupportedFederation& Federation)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bLocalOnly = Serializable->bLocalOnly;
		ServiceName = Serializable->ServiceName;
		RoutingKey = Serializable->RoutingKey;
		Federation = Serializable->Federation;
	}
		
}

