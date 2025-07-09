
#include "BeamableCore/Public/AutoGen/ServiceStorageReferenceLibrary.h"

#include "CoreMinimal.h"


FString UServiceStorageReferenceLibrary::ServiceStorageReferenceToJsonString(const UServiceStorageReference* Serializable, const bool Pretty)
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

UServiceStorageReference* UServiceStorageReferenceLibrary::Make(FOptionalBool bArchived, FOptionalBool bEnabled, FOptionalString Id, FOptionalString StorageType, FOptionalString TemplateId, FOptionalString Checksum, UObject* Outer)
{
	auto Serializable = NewObject<UServiceStorageReference>(Outer);
	Serializable->bArchived = bArchived;
	Serializable->bEnabled = bEnabled;
	Serializable->Id = Id;
	Serializable->StorageType = StorageType;
	Serializable->TemplateId = TemplateId;
	Serializable->Checksum = Checksum;
	
	return Serializable;
}

void UServiceStorageReferenceLibrary::Break(const UServiceStorageReference* Serializable, FOptionalBool& bArchived, FOptionalBool& bEnabled, FOptionalString& Id, FOptionalString& StorageType, FOptionalString& TemplateId, FOptionalString& Checksum)
{
	bArchived = Serializable->bArchived;
	bEnabled = Serializable->bEnabled;
	Id = Serializable->Id;
	StorageType = Serializable->StorageType;
	TemplateId = Serializable->TemplateId;
	Checksum = Serializable->Checksum;
		
}

