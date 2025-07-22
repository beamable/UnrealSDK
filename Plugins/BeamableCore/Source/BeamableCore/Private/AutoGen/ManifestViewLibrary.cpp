
#include "BeamableCore/Public/AutoGen/ManifestViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UManifestViewLibrary::ManifestViewToJsonString(const UManifestView* Serializable, const bool Pretty)
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

UManifestView* UManifestViewLibrary::Make(FString Id, FString Checksum, int64 Created, TArray<UServiceReference*> Manifest, FOptionalInt64 CreatedByAccountId, FOptionalString Comments, FOptionalArrayOfServiceStorageReference StorageReference, UObject* Outer)
{
	auto Serializable = NewObject<UManifestView>(Outer);
	Serializable->Id = Id;
	Serializable->Checksum = Checksum;
	Serializable->Created = Created;
	Serializable->Manifest = Manifest;
	Serializable->CreatedByAccountId = CreatedByAccountId;
	Serializable->Comments = Comments;
	Serializable->StorageReference = StorageReference;
	
	return Serializable;
}

void UManifestViewLibrary::Break(const UManifestView* Serializable, FString& Id, FString& Checksum, int64& Created, TArray<UServiceReference*>& Manifest, FOptionalInt64& CreatedByAccountId, FOptionalString& Comments, FOptionalArrayOfServiceStorageReference& StorageReference)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Checksum = Serializable->Checksum;
		Created = Serializable->Created;
		Manifest = Serializable->Manifest;
		CreatedByAccountId = Serializable->CreatedByAccountId;
		Comments = Serializable->Comments;
		StorageReference = Serializable->StorageReference;
	}
		
}

