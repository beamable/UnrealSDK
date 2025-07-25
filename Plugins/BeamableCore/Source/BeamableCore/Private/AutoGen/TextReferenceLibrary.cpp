
#include "BeamableCore/Public/AutoGen/TextReferenceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTextReferenceLibrary::TextReferenceToJsonString(const UTextReference* Serializable, const bool Pretty)
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

UTextReference* UTextReferenceLibrary::Make(FString Uri, FString Version, FBeamContentId Id, FString Type, FString Visibility, TArray<FString> Tags, FOptionalString Checksum, FOptionalInt64 LastChanged, FOptionalInt64 Created, UObject* Outer)
{
	auto Serializable = NewObject<UTextReference>(Outer);
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

void UTextReferenceLibrary::Break(const UTextReference* Serializable, FString& Uri, FString& Version, FBeamContentId& Id, FString& Type, FString& Visibility, TArray<FString>& Tags, FOptionalString& Checksum, FOptionalInt64& LastChanged, FOptionalInt64& Created)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
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

