
#include "AutoGen/ManifestChecksumsLibrary.h"

#include "CoreMinimal.h"


FString UManifestChecksumsLibrary::ManifestChecksumsToJsonString(const UManifestChecksums* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UManifestChecksums* UManifestChecksumsLibrary::Make(TArray<UManifestChecksum*> Manifests, UObject* Outer)
{
	auto Serializable = NewObject<UManifestChecksums>(Outer);
	Serializable->Manifests = Manifests;
	
	return Serializable;
}

void UManifestChecksumsLibrary::Break(const UManifestChecksums* Serializable, TArray<UManifestChecksum*>& Manifests)
{
	Manifests = Serializable->Manifests;
		
}
