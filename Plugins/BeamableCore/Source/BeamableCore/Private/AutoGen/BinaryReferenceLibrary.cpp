
#include "BeamableCore/Public/AutoGen/BinaryReferenceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBinaryReferenceLibrary::BinaryReferenceToJsonString(const UBinaryReference* Serializable, const bool Pretty)
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

UBinaryReference* UBinaryReferenceLibrary::Make(FString UploadMethod, FString Uri, FString Version, FBeamContentId Id, FString UploadUri, FString Type, FString Visibility, TArray<FString> Tags, FOptionalString Checksum, FOptionalString LastChanged, FOptionalString Created, UObject* Outer)
{
	auto Serializable = NewObject<UBinaryReference>(Outer);
	Serializable->UploadMethod = UploadMethod;
	Serializable->Uri = Uri;
	Serializable->Version = Version;
	Serializable->Id = Id;
	Serializable->UploadUri = UploadUri;
	Serializable->Type = Type;
	Serializable->Visibility = Visibility;
	Serializable->Tags = Tags;
	Serializable->Checksum = Checksum;
	Serializable->LastChanged = LastChanged;
	Serializable->Created = Created;
	
	return Serializable;
}

void UBinaryReferenceLibrary::Break(const UBinaryReference* Serializable, FString& UploadMethod, FString& Uri, FString& Version, FBeamContentId& Id, FString& UploadUri, FString& Type, FString& Visibility, TArray<FString>& Tags, FOptionalString& Checksum, FOptionalString& LastChanged, FOptionalString& Created)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		UploadMethod = Serializable->UploadMethod;
		Uri = Serializable->Uri;
		Version = Serializable->Version;
		Id = Serializable->Id;
		UploadUri = Serializable->UploadUri;
		Type = Serializable->Type;
		Visibility = Serializable->Visibility;
		Tags = Serializable->Tags;
		Checksum = Serializable->Checksum;
		LastChanged = Serializable->LastChanged;
		Created = Serializable->Created;
	}
		
}

