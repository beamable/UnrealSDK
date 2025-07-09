
#include "BeamableCore/Public/AutoGen/BeamoActorManifestChecksumLibrary.h"

#include "CoreMinimal.h"


FString UBeamoActorManifestChecksumLibrary::BeamoActorManifestChecksumToJsonString(const UBeamoActorManifestChecksum* Serializable, const bool Pretty)
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

UBeamoActorManifestChecksum* UBeamoActorManifestChecksumLibrary::Make(FOptionalString Id, FOptionalString Checksum, FOptionalDateTime CreatedAt, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoActorManifestChecksum>(Outer);
	Serializable->Id = Id;
	Serializable->Checksum = Checksum;
	Serializable->CreatedAt = CreatedAt;
	
	return Serializable;
}

void UBeamoActorManifestChecksumLibrary::Break(const UBeamoActorManifestChecksum* Serializable, FOptionalString& Id, FOptionalString& Checksum, FOptionalDateTime& CreatedAt)
{
	Id = Serializable->Id;
	Checksum = Serializable->Checksum;
	CreatedAt = Serializable->CreatedAt;
		
}

