
#include "AutoGen/GetManifestsResponseLibrary.h"

#include "CoreMinimal.h"


FString UGetManifestsResponseLibrary::GetManifestsResponseToJsonString(const UGetManifestsResponse* Serializable, const bool Pretty)
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

UGetManifestsResponse* UGetManifestsResponseLibrary::Make(TArray<UManifestView*> Manifests, UObject* Outer)
{
	auto Serializable = NewObject<UGetManifestsResponse>(Outer);
	Serializable->Manifests = Manifests;
	
	return Serializable;
}

void UGetManifestsResponseLibrary::Break(const UGetManifestsResponse* Serializable, TArray<UManifestView*>& Manifests)
{
	Manifests = Serializable->Manifests;
		
}
