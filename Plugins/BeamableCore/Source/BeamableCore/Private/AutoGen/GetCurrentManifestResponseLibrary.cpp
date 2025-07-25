
#include "BeamableCore/Public/AutoGen/GetCurrentManifestResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetCurrentManifestResponseLibrary::GetCurrentManifestResponseToJsonString(const UGetCurrentManifestResponse* Serializable, const bool Pretty)
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

UGetCurrentManifestResponse* UGetCurrentManifestResponseLibrary::Make(UManifestView* Manifest, UObject* Outer)
{
	auto Serializable = NewObject<UGetCurrentManifestResponse>(Outer);
	Serializable->Manifest = Manifest;
	
	return Serializable;
}

void UGetCurrentManifestResponseLibrary::Break(const UGetCurrentManifestResponse* Serializable, UManifestView*& Manifest)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Manifest = Serializable->Manifest;
	}
		
}

