
#include "BeamableCore/Public/AutoGen/GetManifestResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetManifestResponseLibrary::GetManifestResponseToJsonString(const UGetManifestResponse* Serializable, const bool Pretty)
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

UGetManifestResponse* UGetManifestResponseLibrary::Make(UManifestView* Manifest, UObject* Outer)
{
	auto Serializable = NewObject<UGetManifestResponse>(Outer);
	Serializable->Manifest = Manifest;
	
	return Serializable;
}

void UGetManifestResponseLibrary::Break(const UGetManifestResponse* Serializable, UManifestView*& Manifest)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Manifest = Serializable->Manifest;
	}
		
}

