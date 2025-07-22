
#include "BeamableCore/Public/AutoGen/BeamoV2GetManifestsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2GetManifestsResponseLibrary::BeamoV2GetManifestsResponseToJsonString(const UBeamoV2GetManifestsResponse* Serializable, const bool Pretty)
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

UBeamoV2GetManifestsResponse* UBeamoV2GetManifestsResponseLibrary::Make(FOptionalArrayOfBeamoV2Manifest Manifests, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2GetManifestsResponse>(Outer);
	Serializable->Manifests = Manifests;
	
	return Serializable;
}

void UBeamoV2GetManifestsResponseLibrary::Break(const UBeamoV2GetManifestsResponse* Serializable, FOptionalArrayOfBeamoV2Manifest& Manifests)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Manifests = Serializable->Manifests;
	}
		
}

