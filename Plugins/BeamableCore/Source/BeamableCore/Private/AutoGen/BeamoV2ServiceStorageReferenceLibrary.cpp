
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceStorageReferenceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ServiceStorageReferenceLibrary::BeamoV2ServiceStorageReferenceToJsonString(const UBeamoV2ServiceStorageReference* Serializable, const bool Pretty)
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

UBeamoV2ServiceStorageReference* UBeamoV2ServiceStorageReferenceLibrary::Make(FOptionalBool bArchived, FOptionalBool bEnabled, FOptionalString Id, FOptionalString StorageType, FOptionalString TemplateId, FOptionalString Checksum, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ServiceStorageReference>(Outer);
	Serializable->bArchived = bArchived;
	Serializable->bEnabled = bEnabled;
	Serializable->Id = Id;
	Serializable->StorageType = StorageType;
	Serializable->TemplateId = TemplateId;
	Serializable->Checksum = Checksum;
	
	return Serializable;
}

void UBeamoV2ServiceStorageReferenceLibrary::Break(const UBeamoV2ServiceStorageReference* Serializable, FOptionalBool& bArchived, FOptionalBool& bEnabled, FOptionalString& Id, FOptionalString& StorageType, FOptionalString& TemplateId, FOptionalString& Checksum)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bArchived = Serializable->bArchived;
		bEnabled = Serializable->bEnabled;
		Id = Serializable->Id;
		StorageType = Serializable->StorageType;
		TemplateId = Serializable->TemplateId;
		Checksum = Serializable->Checksum;
	}
		
}

