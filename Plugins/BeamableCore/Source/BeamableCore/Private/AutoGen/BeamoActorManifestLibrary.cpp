
#include "BeamableCore/Public/AutoGen/BeamoActorManifestLibrary.h"

#include "CoreMinimal.h"


FString UBeamoActorManifestLibrary::BeamoActorManifestToJsonString(const UBeamoActorManifest* Serializable, const bool Pretty)
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

UBeamoActorManifest* UBeamoActorManifestLibrary::Make(FOptionalString Id, FOptionalInt64 Created, FOptionalInt64 CreatedByAccountId, FOptionalString Checksum, FOptionalString Comments, FOptionalString StorageGroupId, FOptionalArrayOfBeamoActorServiceReference ServiceReferences, FOptionalArrayOfServiceStorageReference StorageReferences, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoActorManifest>(Outer);
	Serializable->Id = Id;
	Serializable->Created = Created;
	Serializable->CreatedByAccountId = CreatedByAccountId;
	Serializable->Checksum = Checksum;
	Serializable->Comments = Comments;
	Serializable->StorageGroupId = StorageGroupId;
	Serializable->ServiceReferences = ServiceReferences;
	Serializable->StorageReferences = StorageReferences;
	
	return Serializable;
}

void UBeamoActorManifestLibrary::Break(const UBeamoActorManifest* Serializable, FOptionalString& Id, FOptionalInt64& Created, FOptionalInt64& CreatedByAccountId, FOptionalString& Checksum, FOptionalString& Comments, FOptionalString& StorageGroupId, FOptionalArrayOfBeamoActorServiceReference& ServiceReferences, FOptionalArrayOfServiceStorageReference& StorageReferences)
{
	Id = Serializable->Id;
	Created = Serializable->Created;
	CreatedByAccountId = Serializable->CreatedByAccountId;
	Checksum = Serializable->Checksum;
	Comments = Serializable->Comments;
	StorageGroupId = Serializable->StorageGroupId;
	ServiceReferences = Serializable->ServiceReferences;
	StorageReferences = Serializable->StorageReferences;
		
}

