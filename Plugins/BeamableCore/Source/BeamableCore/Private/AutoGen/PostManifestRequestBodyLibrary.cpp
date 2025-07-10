
#include "BeamableCore/Public/AutoGen/PostManifestRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UPostManifestRequestBodyLibrary::PostManifestRequestBodyToJsonString(const UPostManifestRequestBody* Serializable, const bool Pretty)
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

UPostManifestRequestBody* UPostManifestRequestBodyLibrary::Make(FOptionalBool bAutoDeploy, FOptionalString Comments, FOptionalArrayOfBeamoActorServiceReference Manifest, FOptionalArrayOfServiceStorageReference StorageReferences, UObject* Outer)
{
	auto Serializable = NewObject<UPostManifestRequestBody>(Outer);
	Serializable->bAutoDeploy = bAutoDeploy;
	Serializable->Comments = Comments;
	Serializable->Manifest = Manifest;
	Serializable->StorageReferences = StorageReferences;
	
	return Serializable;
}

void UPostManifestRequestBodyLibrary::Break(const UPostManifestRequestBody* Serializable, FOptionalBool& bAutoDeploy, FOptionalString& Comments, FOptionalArrayOfBeamoActorServiceReference& Manifest, FOptionalArrayOfServiceStorageReference& StorageReferences)
{
	bAutoDeploy = Serializable->bAutoDeploy;
	Comments = Serializable->Comments;
	Manifest = Serializable->Manifest;
	StorageReferences = Serializable->StorageReferences;
		
}

