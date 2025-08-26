
#include "BeamableCore/Public/AutoGen/UploadRequestFromPortalLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUploadRequestFromPortalLibrary::UploadRequestFromPortalToJsonString(const UUploadRequestFromPortal* Serializable, const bool Pretty)
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

UUploadRequestFromPortal* UUploadRequestFromPortalLibrary::Make(FString ObjectKey, int64 SizeInBytes, FOptionalInt64 LastModified, FOptionalArrayOfMetadataPair Metadata, UObject* Outer)
{
	auto Serializable = NewObject<UUploadRequestFromPortal>(Outer);
	Serializable->ObjectKey = ObjectKey;
	Serializable->SizeInBytes = SizeInBytes;
	Serializable->LastModified = LastModified;
	Serializable->Metadata = Metadata;
	
	return Serializable;
}

void UUploadRequestFromPortalLibrary::Break(const UUploadRequestFromPortal* Serializable, FString& ObjectKey, int64& SizeInBytes, FOptionalInt64& LastModified, FOptionalArrayOfMetadataPair& Metadata)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ObjectKey = Serializable->ObjectKey;
		SizeInBytes = Serializable->SizeInBytes;
		LastModified = Serializable->LastModified;
		Metadata = Serializable->Metadata;
	}
		
}

