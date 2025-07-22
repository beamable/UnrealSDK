
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceRegistrationResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ServiceRegistrationResponseLibrary::BeamoV2ServiceRegistrationResponseToJsonString(const UBeamoV2ServiceRegistrationResponse* Serializable, const bool Pretty)
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

UBeamoV2ServiceRegistrationResponse* UBeamoV2ServiceRegistrationResponseLibrary::Make(FOptionalArrayOfBeamoV2ServiceRegistration Registrations, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ServiceRegistrationResponse>(Outer);
	Serializable->Registrations = Registrations;
	
	return Serializable;
}

void UBeamoV2ServiceRegistrationResponseLibrary::Break(const UBeamoV2ServiceRegistrationResponse* Serializable, FOptionalArrayOfBeamoV2ServiceRegistration& Registrations)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Registrations = Serializable->Registrations;
	}
		
}

