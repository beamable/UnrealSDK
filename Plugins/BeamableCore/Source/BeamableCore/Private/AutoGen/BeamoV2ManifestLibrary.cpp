
#include "BeamableCore/Public/AutoGen/BeamoV2ManifestLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ManifestLibrary::BeamoV2ManifestToJsonString(const UBeamoV2Manifest* Serializable, const bool Pretty)
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

UBeamoV2Manifest* UBeamoV2ManifestLibrary::Make(FOptionalString Id, FOptionalInt64 Created, FOptionalInt64 CreatedByAccountId, FOptionalString Checksum, FOptionalString Comments, FOptionalString StorageGroupId, FOptionalArrayOfBeamoV2ServiceReference ServiceReferences, FOptionalArrayOfBeamoV2ServiceStorageReference StorageReferences, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2Manifest>(Outer);
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

void UBeamoV2ManifestLibrary::Break(const UBeamoV2Manifest* Serializable, FOptionalString& Id, FOptionalInt64& Created, FOptionalInt64& CreatedByAccountId, FOptionalString& Checksum, FOptionalString& Comments, FOptionalString& StorageGroupId, FOptionalArrayOfBeamoV2ServiceReference& ServiceReferences, FOptionalArrayOfBeamoV2ServiceStorageReference& StorageReferences)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
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
		
}

