
#include "BeamableCore/Public/AutoGen/BeamoV2FederationRegistrationResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2FederationRegistrationResponseLibrary::BeamoV2FederationRegistrationResponseToJsonString(const UBeamoV2FederationRegistrationResponse* Serializable, const bool Pretty)
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

UBeamoV2FederationRegistrationResponse* UBeamoV2FederationRegistrationResponseLibrary::Make(FOptionalArrayOfBeamoV2FederationRegistration Registrations, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2FederationRegistrationResponse>(Outer);
	Serializable->Registrations = Registrations;
	
	return Serializable;
}

void UBeamoV2FederationRegistrationResponseLibrary::Break(const UBeamoV2FederationRegistrationResponse* Serializable, FOptionalArrayOfBeamoV2FederationRegistration& Registrations)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Registrations = Serializable->Registrations;
	}
		
}

