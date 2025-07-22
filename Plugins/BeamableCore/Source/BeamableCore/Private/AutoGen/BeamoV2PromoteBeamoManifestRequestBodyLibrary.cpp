
#include "BeamableCore/Public/AutoGen/BeamoV2PromoteBeamoManifestRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2PromoteBeamoManifestRequestBodyLibrary::BeamoV2PromoteBeamoManifestRequestBodyToJsonString(const UBeamoV2PromoteBeamoManifestRequestBody* Serializable, const bool Pretty)
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

UBeamoV2PromoteBeamoManifestRequestBody* UBeamoV2PromoteBeamoManifestRequestBodyLibrary::Make(FString SourceRealmId, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2PromoteBeamoManifestRequestBody>(Outer);
	Serializable->SourceRealmId = SourceRealmId;
	
	return Serializable;
}

void UBeamoV2PromoteBeamoManifestRequestBodyLibrary::Break(const UBeamoV2PromoteBeamoManifestRequestBody* Serializable, FString& SourceRealmId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SourceRealmId = Serializable->SourceRealmId;
	}
		
}

