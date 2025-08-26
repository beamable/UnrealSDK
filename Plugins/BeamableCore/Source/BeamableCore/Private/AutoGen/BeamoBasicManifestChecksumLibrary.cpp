
#include "BeamableCore/Public/AutoGen/BeamoBasicManifestChecksumLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoBasicManifestChecksumLibrary::BeamoBasicManifestChecksumToJsonString(const UBeamoBasicManifestChecksum* Serializable, const bool Pretty)
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

UBeamoBasicManifestChecksum* UBeamoBasicManifestChecksumLibrary::Make(FString Id, FString Checksum, int64 CreatedAt, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoBasicManifestChecksum>(Outer);
	Serializable->Id = Id;
	Serializable->Checksum = Checksum;
	Serializable->CreatedAt = CreatedAt;
	
	return Serializable;
}

void UBeamoBasicManifestChecksumLibrary::Break(const UBeamoBasicManifestChecksum* Serializable, FString& Id, FString& Checksum, int64& CreatedAt)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Checksum = Serializable->Checksum;
		CreatedAt = Serializable->CreatedAt;
	}
		
}

