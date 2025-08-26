
#include "BeamableCore/Public/AutoGen/ContentBasicManifestChecksumLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UContentBasicManifestChecksumLibrary::ContentBasicManifestChecksumToJsonString(const UContentBasicManifestChecksum* Serializable, const bool Pretty)
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

UContentBasicManifestChecksum* UContentBasicManifestChecksumLibrary::Make(FBeamContentManifestId Id, FString Checksum, int64 CreatedAt, FOptionalBool bArchived, FOptionalString Uid, UObject* Outer)
{
	auto Serializable = NewObject<UContentBasicManifestChecksum>(Outer);
	Serializable->Id = Id;
	Serializable->Checksum = Checksum;
	Serializable->CreatedAt = CreatedAt;
	Serializable->bArchived = bArchived;
	Serializable->Uid = Uid;
	
	return Serializable;
}

void UContentBasicManifestChecksumLibrary::Break(const UContentBasicManifestChecksum* Serializable, FBeamContentManifestId& Id, FString& Checksum, int64& CreatedAt, FOptionalBool& bArchived, FOptionalString& Uid)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Checksum = Serializable->Checksum;
		CreatedAt = Serializable->CreatedAt;
		bArchived = Serializable->bArchived;
		Uid = Serializable->Uid;
	}
		
}

