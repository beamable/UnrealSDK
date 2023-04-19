
#include "BeamableCore/Public/AutoGen/ContentMetaLibrary.h"

#include "CoreMinimal.h"


FString UContentMetaLibrary::ContentMetaToJsonString(const UContentMeta* Serializable, const bool Pretty)
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

UContentMeta* UContentMetaLibrary::Make(EContentVisibility Visibility, FOptionalString Text, FOptionalString Data, UObject* Outer)
{
	auto Serializable = NewObject<UContentMeta>(Outer);
	Serializable->Visibility = Visibility;
	Serializable->Text = Text;
	Serializable->Data = Data;
	
	return Serializable;
}

void UContentMetaLibrary::Break(const UContentMeta* Serializable, EContentVisibility& Visibility, FOptionalString& Text, FOptionalString& Data)
{
	Visibility = Serializable->Visibility;
	Text = Serializable->Text;
	Data = Serializable->Data;
		
}

