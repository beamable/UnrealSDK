
#include "BeamableCore/Public/AutoGen/ManifestSummaryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UManifestSummaryLibrary::ManifestSummaryToJsonString(const UManifestSummary* Serializable, const bool Pretty)
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

UManifestSummary* UManifestSummaryLibrary::Make(FString Uid, UContentBasicManifestChecksum* Manifest, UObject* Outer)
{
	auto Serializable = NewObject<UManifestSummary>(Outer);
	Serializable->Uid = Uid;
	Serializable->Manifest = Manifest;
	
	return Serializable;
}

void UManifestSummaryLibrary::Break(const UManifestSummary* Serializable, FString& Uid, UContentBasicManifestChecksum*& Manifest)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Uid = Serializable->Uid;
		Manifest = Serializable->Manifest;
	}
		
}

