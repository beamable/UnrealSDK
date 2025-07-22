
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceRegistrationRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ServiceRegistrationRequestBodyLibrary::BeamoV2ServiceRegistrationRequestBodyToJsonString(const UBeamoV2ServiceRegistrationRequestBody* Serializable, const bool Pretty)
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

UBeamoV2ServiceRegistrationRequestBody* UBeamoV2ServiceRegistrationRequestBodyLibrary::Make(FOptionalString RoutingKey, FOptionalBool bTrafficFilterEnabled, FOptionalArrayOfBeamoV2SupportedFederation Federation, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ServiceRegistrationRequestBody>(Outer);
	Serializable->RoutingKey = RoutingKey;
	Serializable->bTrafficFilterEnabled = bTrafficFilterEnabled;
	Serializable->Federation = Federation;
	
	return Serializable;
}

void UBeamoV2ServiceRegistrationRequestBodyLibrary::Break(const UBeamoV2ServiceRegistrationRequestBody* Serializable, FOptionalString& RoutingKey, FOptionalBool& bTrafficFilterEnabled, FOptionalArrayOfBeamoV2SupportedFederation& Federation)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		RoutingKey = Serializable->RoutingKey;
		bTrafficFilterEnabled = Serializable->bTrafficFilterEnabled;
		Federation = Serializable->Federation;
	}
		
}

