
#include "BeamableCore/Public/AutoGen/ContentReferenceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UContentReferenceLibrary::ContentReferenceToJsonString(const UContentReference* Serializable, const bool Pretty)
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

UContentReference* UContentReferenceLibrary::Make(FString Tag, FString Uri, FString Version, FBeamContentId Id, FString Type, EBeamContentVisibility Visibility, TArray<FString> Tags, FOptionalString Checksum, FOptionalInt64 LastChanged, FOptionalInt64 Created, UObject* Outer)
{
	auto Serializable = NewObject<UContentReference>(Outer);
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

void UContentReferenceLibrary::Break(const UContentReference* Serializable, FString& Tag, FString& Uri, FString& Version, FBeamContentId& Id, FString& Type, EBeamContentVisibility& Visibility, TArray<FString>& Tags, FOptionalString& Checksum, FOptionalInt64& LastChanged, FOptionalInt64& Created)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
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
		
}

