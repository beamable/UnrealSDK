
#include "BeamableCore/Public/AutoGen/ClientManifestJsonResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


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

UClientManifestJsonResponse* UClientManifestJsonResponseLibrary::Make(TArray<FBeamRemoteContentManifestEntry> Entries, FOptionalString Uid, FOptionalInt64 PublisherAccountId, UObject* Outer)
{
	auto Serializable = NewObject<UClientManifestJsonResponse>(Outer);
	Serializable->Entries = Entries;
	Serializable->Uid = Uid;
	Serializable->PublisherAccountId = PublisherAccountId;
	
	return Serializable;
}

void UClientManifestJsonResponseLibrary::Break(const UClientManifestJsonResponse* Serializable, TArray<FBeamRemoteContentManifestEntry>& Entries, FOptionalString& Uid, FOptionalInt64& PublisherAccountId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Entries = Serializable->Entries;
		Uid = Serializable->Uid;
		PublisherAccountId = Serializable->PublisherAccountId;
	}
		
}

