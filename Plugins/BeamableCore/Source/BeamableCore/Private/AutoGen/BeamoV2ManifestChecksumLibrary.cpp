
#include "BeamableCore/Public/AutoGen/BeamoV2ManifestChecksumLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ManifestChecksumLibrary::BeamoV2ManifestChecksumToJsonString(const UBeamoV2ManifestChecksum* Serializable, const bool Pretty)
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

UBeamoV2ManifestChecksum* UBeamoV2ManifestChecksumLibrary::Make(FOptionalString Id, FOptionalString Checksum, FOptionalDateTime CreatedAt, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ManifestChecksum>(Outer);
	Serializable->Id = Id;
	Serializable->Checksum = Checksum;
	Serializable->CreatedAt = CreatedAt;
	
	return Serializable;
}

void UBeamoV2ManifestChecksumLibrary::Break(const UBeamoV2ManifestChecksum* Serializable, FOptionalString& Id, FOptionalString& Checksum, FOptionalDateTime& CreatedAt)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Checksum = Serializable->Checksum;
		CreatedAt = Serializable->CreatedAt;
	}
		
}

