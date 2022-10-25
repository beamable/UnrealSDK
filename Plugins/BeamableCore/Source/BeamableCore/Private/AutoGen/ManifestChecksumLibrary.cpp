
#include "AutoGen/ManifestChecksumLibrary.h"

#include "CoreMinimal.h"


FString UManifestChecksumLibrary::ManifestChecksumToJsonString(const UManifestChecksum* Serializable, const bool Pretty)
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

UManifestChecksum* UManifestChecksumLibrary::Make(FString Id, FString Checksum, int64 CreatedAt, UObject* Outer)
{
	auto Serializable = NewObject<UManifestChecksum>(Outer);
	Serializable->Id = Id;
	Serializable->Checksum = Checksum;
	Serializable->CreatedAt = CreatedAt;
	
	return Serializable;
}

void UManifestChecksumLibrary::Break(const UManifestChecksum* Serializable, FString& Id, FString& Checksum, int64& CreatedAt)
{
	Id = Serializable->Id;
	Checksum = Serializable->Checksum;
	CreatedAt = Serializable->CreatedAt;
		
}

