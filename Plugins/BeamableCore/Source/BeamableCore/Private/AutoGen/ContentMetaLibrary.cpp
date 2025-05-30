#include "BeamableCore/Public/AutoGen/ContentMetaLibrary.h"

#include "CoreMinimal.h"


FString UContentMetaLibrary::ContentMetaToJsonString(const UContentMeta* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if (Pretty)
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

UContentMeta* UContentMetaLibrary::Make(EBeamContentVisibility Visibility, FOptionalString Text, UObject* Outer)
{
	auto Serializable = NewObject<UContentMeta>(Outer);
	Serializable->Visibility = Visibility;
	Serializable->Text = Text;

	return Serializable;
}

void UContentMetaLibrary::Break(const UContentMeta* Serializable, EBeamContentVisibility& Visibility, FOptionalString& Text)
{
	Visibility = Serializable->Visibility;
	Text = Serializable->Text;
}
