
#include "BeamableCore/Public/AutoGen/BeamoV2GetServiceSecretResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2GetServiceSecretResponseLibrary::BeamoV2GetServiceSecretResponseToJsonString(const UBeamoV2GetServiceSecretResponse* Serializable, const bool Pretty)
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

UBeamoV2GetServiceSecretResponse* UBeamoV2GetServiceSecretResponseLibrary::Make(FOptionalString Secret, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2GetServiceSecretResponse>(Outer);
	Serializable->Secret = Secret;
	
	return Serializable;
}

void UBeamoV2GetServiceSecretResponseLibrary::Break(const UBeamoV2GetServiceSecretResponse* Serializable, FOptionalString& Secret)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Secret = Serializable->Secret;
	}
		
}

