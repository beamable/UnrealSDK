
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceRegistrationQueryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ServiceRegistrationQueryLibrary::BeamoV2ServiceRegistrationQueryToJsonString(const UBeamoV2ServiceRegistrationQuery* Serializable, const bool Pretty)
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

UBeamoV2ServiceRegistrationQuery* UBeamoV2ServiceRegistrationQueryLibrary::Make(FOptionalBool bLocalOnly, FOptionalString ServiceName, FOptionalString RoutingKey, FOptionalBeamoV2SupportedFederation Federation, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ServiceRegistrationQuery>(Outer);
	Serializable->bLocalOnly = bLocalOnly;
	Serializable->ServiceName = ServiceName;
	Serializable->RoutingKey = RoutingKey;
	Serializable->Federation = Federation;
	
	return Serializable;
}

void UBeamoV2ServiceRegistrationQueryLibrary::Break(const UBeamoV2ServiceRegistrationQuery* Serializable, FOptionalBool& bLocalOnly, FOptionalString& ServiceName, FOptionalString& RoutingKey, FOptionalBeamoV2SupportedFederation& Federation)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bLocalOnly = Serializable->bLocalOnly;
		ServiceName = Serializable->ServiceName;
		RoutingKey = Serializable->RoutingKey;
		Federation = Serializable->Federation;
	}
		
}

