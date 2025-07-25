
#include "BeamableCore/Public/AutoGen/ServiceStorageReferenceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


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

UServiceStorageReference* UServiceStorageReferenceLibrary::Make(bool bArchived, bool bEnabled, FString StorageType, FString Id, FString Checksum, FOptionalString TemplateId, UObject* Outer)
{
	auto Serializable = NewObject<UServiceStorageReference>(Outer);
	Serializable->bArchived = bArchived;
	Serializable->bEnabled = bEnabled;
	Serializable->StorageType = StorageType;
	Serializable->Id = Id;
	Serializable->Checksum = Checksum;
	Serializable->TemplateId = TemplateId;
	
	return Serializable;
}

void UServiceStorageReferenceLibrary::Break(const UServiceStorageReference* Serializable, bool& bArchived, bool& bEnabled, FString& StorageType, FString& Id, FString& Checksum, FOptionalString& TemplateId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bArchived = Serializable->bArchived;
		bEnabled = Serializable->bEnabled;
		StorageType = Serializable->StorageType;
		Id = Serializable->Id;
		Checksum = Serializable->Checksum;
		TemplateId = Serializable->TemplateId;
	}
		
}

