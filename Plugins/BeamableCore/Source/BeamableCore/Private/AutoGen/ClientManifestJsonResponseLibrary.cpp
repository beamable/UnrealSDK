
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

UClientManifestJsonResponse* UClientManifestJsonResponseLibrary::Make(TArray<FBeamRemoteContentManifestEntry> Entries, FOptionalInt64 LatestUpdate, FOptionalInt64 PublisherAccountId, FOptionalInt64 CreatedAt, FOptionalString Uid, UObject* Outer)
{
	auto Serializable = NewObject<UClientManifestJsonResponse>(Outer);
	Serializable->Entries = Entries;
	Serializable->LatestUpdate = LatestUpdate;
	Serializable->PublisherAccountId = PublisherAccountId;
	Serializable->CreatedAt = CreatedAt;
	Serializable->Uid = Uid;
	
	return Serializable;
}

void UClientManifestJsonResponseLibrary::Break(const UClientManifestJsonResponse* Serializable, TArray<FBeamRemoteContentManifestEntry>& Entries, FOptionalInt64& LatestUpdate, FOptionalInt64& PublisherAccountId, FOptionalInt64& CreatedAt, FOptionalString& Uid)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Entries = Serializable->Entries;
		LatestUpdate = Serializable->LatestUpdate;
		PublisherAccountId = Serializable->PublisherAccountId;
		CreatedAt = Serializable->CreatedAt;
		Uid = Serializable->Uid;
	}
		
}

