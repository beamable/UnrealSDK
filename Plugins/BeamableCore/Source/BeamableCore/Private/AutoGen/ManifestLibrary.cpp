
#include "AutoGen/ManifestLibrary.h"

#include "CoreMinimal.h"


FString UManifestLibrary::ManifestToJsonString(const UManifest* Serializable, const bool Pretty)
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

UManifest* UManifestLibrary::Make(bool bReplacement, FString Id, int64 Created, TArray<UReference*> Manifest, UObject* Outer)
{
	auto Serializable = NewObject<UManifest>(Outer);
	Serializable->bReplacement = bReplacement;
	Serializable->Id = Id;
	Serializable->Created = Created;
	Serializable->Manifest = Manifest;
	
	return Serializable;
}

void UManifestLibrary::Break(const UManifest* Serializable, bool& bReplacement, FString& Id, int64& Created, TArray<UReference*>& Manifest)
{
	bReplacement = Serializable->bReplacement;
	Id = Serializable->Id;
	Created = Serializable->Created;
	Manifest = Serializable->Manifest;
		
}

