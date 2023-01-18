
#include "AutoGen/ContentReferenceLibrary.h"

#include "CoreMinimal.h"


FString UContentReferenceLibrary::ContentReferenceToJsonString(const UContentReference* Serializable, const bool Pretty)
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

UContentReference* UContentReferenceLibrary::Make(FString ContentPrefix, FString Tag, FString Uri, FString Version, FBeamContentId Id, FString Type, EContentVisibility Visibility, TArray<FString> Tags, FOptionalString Checksum, FOptionalInt64 LastChanged, FOptionalInt64 Created, UObject* Outer)
{
	auto Serializable = NewObject<UContentReference>(Outer);
	Serializable->ContentPrefix = ContentPrefix;
	Serializable->Tag = Tag;
	Serializable->Uri = Uri;
	Serializable->Version = Version;
	Serializable->Id = Id;
	Serializable->Type = Type;
	Serializable->Visibility = Visibility;
	Serializable->Tags = Tags;
	Serializable->Checksum = Checksum;
	Serializable->LastChanged = LastChanged;
	Serializable->Created = Created;
	
	return Serializable;
}

void UContentReferenceLibrary::Break(const UContentReference* Serializable, FString& ContentPrefix, FString& Tag, FString& Uri, FString& Version, FBeamContentId& Id, FString& Type, EContentVisibility& Visibility, TArray<FString>& Tags, FOptionalString& Checksum, FOptionalInt64& LastChanged, FOptionalInt64& Created)
{
	ContentPrefix = Serializable->ContentPrefix;
	Tag = Serializable->Tag;
	Uri = Serializable->Uri;
	Version = Serializable->Version;
	Id = Serializable->Id;
	Type = Serializable->Type;
	Visibility = Serializable->Visibility;
	Tags = Serializable->Tags;
	Checksum = Serializable->Checksum;
	LastChanged = Serializable->LastChanged;
	Created = Serializable->Created;
		
}

