
#include "BeamableCore/Public/AutoGen/BeamoV2DeleteRegistrationRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2DeleteRegistrationRequestBodyLibrary::BeamoV2DeleteRegistrationRequestBodyToJsonString(const UBeamoV2DeleteRegistrationRequestBody* Serializable, const bool Pretty)
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

UBeamoV2DeleteRegistrationRequestBody* UBeamoV2DeleteRegistrationRequestBodyLibrary::Make(FOptionalString RoutingKey, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2DeleteRegistrationRequestBody>(Outer);
	Serializable->RoutingKey = RoutingKey;
	
	return Serializable;
}

void UBeamoV2DeleteRegistrationRequestBodyLibrary::Break(const UBeamoV2DeleteRegistrationRequestBody* Serializable, FOptionalString& RoutingKey)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		RoutingKey = Serializable->RoutingKey;
	}
		
}

