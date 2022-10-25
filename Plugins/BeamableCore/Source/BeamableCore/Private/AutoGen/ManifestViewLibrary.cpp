
#include "AutoGen/ManifestViewLibrary.h"

#include "CoreMinimal.h"


FString UManifestViewLibrary::ManifestViewToJsonString(const UManifestView* Serializable, const bool Pretty)
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

UManifestView* UManifestViewLibrary::Make(int64 CreatedByAccountId, FString Id, FString Checksum, int64 Created, TArray<UServiceReference*> Manifest, FOptionalString Comments, FOptionalArrayOfServiceStorageReference StorageReference, UObject* Outer)
{
	auto Serializable = NewObject<UManifestView>(Outer);
	Serializable->CreatedByAccountId = CreatedByAccountId;
	Serializable->Id = Id;
	Serializable->Checksum = Checksum;
	Serializable->Created = Created;
	Serializable->Manifest = Manifest;
	Serializable->Comments = Comments;
	Serializable->StorageReference = StorageReference;
	
	return Serializable;
}

void UManifestViewLibrary::Break(const UManifestView* Serializable, int64& CreatedByAccountId, FString& Id, FString& Checksum, int64& Created, TArray<UServiceReference*>& Manifest, FOptionalString& Comments, FOptionalArrayOfServiceStorageReference& StorageReference)
{
	CreatedByAccountId = Serializable->CreatedByAccountId;
	Id = Serializable->Id;
	Checksum = Serializable->Checksum;
	Created = Serializable->Created;
	Manifest = Serializable->Manifest;
	Comments = Serializable->Comments;
	StorageReference = Serializable->StorageReference;
		
}

