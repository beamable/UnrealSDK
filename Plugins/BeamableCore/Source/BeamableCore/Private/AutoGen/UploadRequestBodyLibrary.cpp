
#include "BeamableCore/Public/AutoGen/UploadRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUploadRequestBodyLibrary::UploadRequestBodyToJsonString(const UUploadRequestBody* Serializable, const bool Pretty)
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

UUploadRequestBody* UUploadRequestBodyLibrary::Make(FString ObjectKey, int64 SizeInBytes, FOptionalBool bDeleted, FOptionalInt64 LastModified, FOptionalString Checksum, FOptionalArrayOfMetadataPair Metadata, UObject* Outer)
{
	auto Serializable = NewObject<UUploadRequestBody>(Outer);
	Serializable->ObjectKey = ObjectKey;
	Serializable->SizeInBytes = SizeInBytes;
	Serializable->bDeleted = bDeleted;
	Serializable->LastModified = LastModified;
	Serializable->Checksum = Checksum;
	Serializable->Metadata = Metadata;
	
	return Serializable;
}

void UUploadRequestBodyLibrary::Break(const UUploadRequestBody* Serializable, FString& ObjectKey, int64& SizeInBytes, FOptionalBool& bDeleted, FOptionalInt64& LastModified, FOptionalString& Checksum, FOptionalArrayOfMetadataPair& Metadata)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ObjectKey = Serializable->ObjectKey;
		SizeInBytes = Serializable->SizeInBytes;
		bDeleted = Serializable->bDeleted;
		LastModified = Serializable->LastModified;
		Checksum = Serializable->Checksum;
		Metadata = Serializable->Metadata;
	}
		
}

