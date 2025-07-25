
#include "BeamableCore/Public/AutoGen/ManifestChecksumsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UManifestChecksumsLibrary::ManifestChecksumsToJsonString(const UManifestChecksums* Serializable, const bool Pretty)
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

UManifestChecksums* UManifestChecksumsLibrary::Make(TArray<UContentBasicManifestChecksum*> Manifests, UObject* Outer)
{
	auto Serializable = NewObject<UManifestChecksums>(Outer);
	Serializable->Manifests = Manifests;
	
	return Serializable;
}

void UManifestChecksumsLibrary::Break(const UManifestChecksums* Serializable, TArray<UContentBasicManifestChecksum*>& Manifests)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Manifests = Serializable->Manifests;
	}
		
}

