
#include "BeamableCore/Public/AutoGen/ContentBasicManifestChecksumLibrary.h"

#include "CoreMinimal.h"


FString UContentBasicManifestChecksumLibrary::ContentBasicManifestChecksumToJsonString(const UContentBasicManifestChecksum* Serializable, const bool Pretty)
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

UContentBasicManifestChecksum* UContentBasicManifestChecksumLibrary::Make(FBeamContentManifestId Id, FString Checksum, int64 CreatedAt, FOptionalBool bArchived, UObject* Outer)
{
	auto Serializable = NewObject<UContentBasicManifestChecksum>(Outer);
	Serializable->Id = Id;
	Serializable->Checksum = Checksum;
	Serializable->CreatedAt = CreatedAt;
	Serializable->bArchived = bArchived;
	
	return Serializable;
}

void UContentBasicManifestChecksumLibrary::Break(const UContentBasicManifestChecksum* Serializable, FBeamContentManifestId& Id, FString& Checksum, int64& CreatedAt, FOptionalBool& bArchived)
{
	Id = Serializable->Id;
	Checksum = Serializable->Checksum;
	CreatedAt = Serializable->CreatedAt;
	bArchived = Serializable->bArchived;
		
}

