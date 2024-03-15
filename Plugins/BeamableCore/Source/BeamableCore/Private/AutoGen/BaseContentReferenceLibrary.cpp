
#include "BeamableCore/Public/AutoGen/BaseContentReferenceLibrary.h"

#include "CoreMinimal.h"


FString UBaseContentReferenceLibrary::BaseContentReferenceToJsonString(const UBaseContentReference* Serializable, const bool Pretty)
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

UBaseContentReference* UBaseContentReferenceLibrary::Make(UContentReference* Content, UTextReference* Text, UBinaryReference* Binary, UObject* Outer)
{
	auto Serializable = NewObject<UBaseContentReference>(Outer);
	Serializable->Content = Content;
	Serializable->Text = Text;
	Serializable->Binary = Binary;
	
	return Serializable;
}

void UBaseContentReferenceLibrary::Break(const UBaseContentReference* Serializable, UContentReference*& Content, UTextReference*& Text, UBinaryReference*& Binary)
{
	Content = Serializable->Content;
	Text = Serializable->Text;
	Binary = Serializable->Binary;
		
}

