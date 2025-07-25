
#include "BeamableCore/Public/AutoGen/PostManifestRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


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

UPostManifestRequestBody* UPostManifestRequestBodyLibrary::Make(TArray<UServiceReference*> Manifest, FOptionalBool bAutoDeploy, FOptionalString Comments, FOptionalArrayOfServiceStorageReference StorageReferences, UObject* Outer)
{
	auto Serializable = NewObject<UPostManifestRequestBody>(Outer);
	Serializable->Manifest = Manifest;
	Serializable->bAutoDeploy = bAutoDeploy;
	Serializable->Comments = Comments;
	Serializable->StorageReferences = StorageReferences;
	
	return Serializable;
}

void UPostManifestRequestBodyLibrary::Break(const UPostManifestRequestBody* Serializable, TArray<UServiceReference*>& Manifest, FOptionalBool& bAutoDeploy, FOptionalString& Comments, FOptionalArrayOfServiceStorageReference& StorageReferences)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Manifest = Serializable->Manifest;
		bAutoDeploy = Serializable->bAutoDeploy;
		Comments = Serializable->Comments;
		StorageReferences = Serializable->StorageReferences;
	}
		
}

