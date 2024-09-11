
#include "BeamableCore/Public/AutoGen/ClientManifestJsonResponseLibrary.h"

#include "CoreMinimal.h"


FString UClientManifestJsonResponseLibrary::ClientManifestJsonResponseToJsonString(const UClientManifestJsonResponse* Serializable, const bool Pretty)
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

UClientManifestJsonResponse* UClientManifestJsonResponseLibrary::Make(TArray<FBeamRemoteContentManifestEntry> Entries, UObject* Outer)
{
	auto Serializable = NewObject<UClientManifestJsonResponse>(Outer);
	Serializable->Entries = Entries;
	
	return Serializable;
}

void UClientManifestJsonResponseLibrary::Break(const UClientManifestJsonResponse* Serializable, TArray<FBeamRemoteContentManifestEntry>& Entries)
{
	Entries = Serializable->Entries;
		
}

