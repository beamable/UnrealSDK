
#include "BeamableCore/Public/AutoGen/BeamoV2FederationRegistrationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2FederationRegistrationLibrary::BeamoV2FederationRegistrationToJsonString(const UBeamoV2FederationRegistration* Serializable, const bool Pretty)
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

UBeamoV2FederationRegistration* UBeamoV2FederationRegistrationLibrary::Make(FOptionalBool bTrafficFilterEnabled, FOptionalString ServiceName, FOptionalString RoutingKey, FOptionalDateTime Ttl, FOptionalArrayOfBeamoV2SupportedFederation Federation, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2FederationRegistration>(Outer);
	Serializable->bTrafficFilterEnabled = bTrafficFilterEnabled;
	Serializable->ServiceName = ServiceName;
	Serializable->RoutingKey = RoutingKey;
	Serializable->Ttl = Ttl;
	Serializable->Federation = Federation;
	
	return Serializable;
}

void UBeamoV2FederationRegistrationLibrary::Break(const UBeamoV2FederationRegistration* Serializable, FOptionalBool& bTrafficFilterEnabled, FOptionalString& ServiceName, FOptionalString& RoutingKey, FOptionalDateTime& Ttl, FOptionalArrayOfBeamoV2SupportedFederation& Federation)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bTrafficFilterEnabled = Serializable->bTrafficFilterEnabled;
		ServiceName = Serializable->ServiceName;
		RoutingKey = Serializable->RoutingKey;
		Ttl = Serializable->Ttl;
		Federation = Serializable->Federation;
	}
		
}

