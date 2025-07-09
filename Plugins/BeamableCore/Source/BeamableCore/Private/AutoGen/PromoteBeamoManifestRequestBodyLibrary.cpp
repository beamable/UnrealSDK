
#include "BeamableCore/Public/AutoGen/PromoteBeamoManifestRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UPromoteBeamoManifestRequestBodyLibrary::PromoteBeamoManifestRequestBodyToJsonString(const UPromoteBeamoManifestRequestBody* Serializable, const bool Pretty)
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

UPromoteBeamoManifestRequestBody* UPromoteBeamoManifestRequestBodyLibrary::Make(FString SourceRealmId, UObject* Outer)
{
	auto Serializable = NewObject<UPromoteBeamoManifestRequestBody>(Outer);
	Serializable->SourceRealmId = SourceRealmId;
	
	return Serializable;
}

void UPromoteBeamoManifestRequestBodyLibrary::Break(const UPromoteBeamoManifestRequestBody* Serializable, FString& SourceRealmId)
{
	SourceRealmId = Serializable->SourceRealmId;
		
}

