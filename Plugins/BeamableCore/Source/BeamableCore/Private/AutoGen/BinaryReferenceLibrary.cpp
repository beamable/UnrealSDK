
#include "AutoGen/BinaryReferenceLibrary.h"

#include "CoreMinimal.h"


FString UBinaryReferenceLibrary::BinaryReferenceToJsonString(const UBinaryReference* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UBinaryReference* UBinaryReferenceLibrary::Make(FString UploadMethod, FString ContentPrefix, FString Uri, FString Version, FBeamContentId Id, FString UploadUri, FString Type, EContentVisibility Visibility, TArray<FString> Tags, FOptionalString Checksum, FOptionalInt64 LastChanged, FOptionalInt64 Created, UObject* Outer)
{
	auto Serializable = NewObject<UBinaryReference>(Outer);
	Serializable->UploadMethod = UploadMethod;
	Serializable->ContentPrefix = ContentPrefix;
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

void UBinaryReferenceLibrary::Break(const UBinaryReference* Serializable, FString& UploadMethod, FString& ContentPrefix, FString& Uri, FString& Version, FBeamContentId& Id, FString& UploadUri, FString& Type, EContentVisibility& Visibility, TArray<FString>& Tags, FOptionalString& Checksum, FOptionalInt64& LastChanged, FOptionalInt64& Created)
{
	UploadMethod = Serializable->UploadMethod;
	ContentPrefix = Serializable->ContentPrefix;
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

