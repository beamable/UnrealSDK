
#include "BeamableCore/Public/AutoGen/BinaryDefinitionLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBinaryDefinitionLibrary::BinaryDefinitionToJsonString(const UBinaryDefinition* Serializable, const bool Pretty)
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

UBinaryDefinition* UBinaryDefinitionLibrary::Make(FBeamContentId Id, FString Checksum, FString UploadContentType, FOptionalString Visibility, FOptionalArrayOfString Tags, UObject* Outer)
{
	auto Serializable = NewObject<UBinaryDefinition>(Outer);
	Serializable->Id = Id;
	Serializable->Checksum = Checksum;
	Serializable->UploadContentType = UploadContentType;
	Serializable->Visibility = Visibility;
	Serializable->Tags = Tags;
	
	return Serializable;
}

void UBinaryDefinitionLibrary::Break(const UBinaryDefinition* Serializable, FBeamContentId& Id, FString& Checksum, FString& UploadContentType, FOptionalString& Visibility, FOptionalArrayOfString& Tags)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Checksum = Serializable->Checksum;
		UploadContentType = Serializable->UploadContentType;
		Visibility = Serializable->Visibility;
		Tags = Serializable->Tags;
	}
		
}

