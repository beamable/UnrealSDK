
#include "BeamableCore/Public/AutoGen/PostManifestResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPostManifestResponseLibrary::PostManifestResponseToJsonString(const UPostManifestResponse* Serializable, const bool Pretty)
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

UPostManifestResponse* UPostManifestResponseLibrary::Make(FOptionalBeamoBasicManifestChecksum Manifest, UObject* Outer)
{
	auto Serializable = NewObject<UPostManifestResponse>(Outer);
	Serializable->Manifest = Manifest;
	
	return Serializable;
}

void UPostManifestResponseLibrary::Break(const UPostManifestResponse* Serializable, FOptionalBeamoBasicManifestChecksum& Manifest)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Manifest = Serializable->Manifest;
	}
		
}

