
#include "BeamableCore/Public/AutoGen/GetManifestsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetManifestsResponseLibrary::GetManifestsResponseToJsonString(const UGetManifestsResponse* Serializable, const bool Pretty)
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

UGetManifestsResponse* UGetManifestsResponseLibrary::Make(TArray<UContentBasicManifest*> Manifests, UObject* Outer)
{
	auto Serializable = NewObject<UGetManifestsResponse>(Outer);
	Serializable->Manifests = Manifests;
	
	return Serializable;
}

void UGetManifestsResponseLibrary::Break(const UGetManifestsResponse* Serializable, TArray<UContentBasicManifest*>& Manifests)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Manifests = Serializable->Manifests;
	}
		
}

