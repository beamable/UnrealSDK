
#include "BeamableCore/Public/AutoGen/BeamoV2PostManifestRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2PostManifestRequestBodyLibrary::BeamoV2PostManifestRequestBodyToJsonString(const UBeamoV2PostManifestRequestBody* Serializable, const bool Pretty)
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

UBeamoV2PostManifestRequestBody* UBeamoV2PostManifestRequestBodyLibrary::Make(FOptionalBool bAutoDeploy, FOptionalString Comments, FOptionalArrayOfBeamoV2ServiceReference Manifest, FOptionalArrayOfBeamoV2ServiceStorageReference StorageReferences, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2PostManifestRequestBody>(Outer);
	Serializable->bAutoDeploy = bAutoDeploy;
	Serializable->Comments = Comments;
	Serializable->Manifest = Manifest;
	Serializable->StorageReferences = StorageReferences;
	
	return Serializable;
}

void UBeamoV2PostManifestRequestBodyLibrary::Break(const UBeamoV2PostManifestRequestBody* Serializable, FOptionalBool& bAutoDeploy, FOptionalString& Comments, FOptionalArrayOfBeamoV2ServiceReference& Manifest, FOptionalArrayOfBeamoV2ServiceStorageReference& StorageReferences)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bAutoDeploy = Serializable->bAutoDeploy;
		Comments = Serializable->Comments;
		Manifest = Serializable->Manifest;
		StorageReferences = Serializable->StorageReferences;
	}
		
}

