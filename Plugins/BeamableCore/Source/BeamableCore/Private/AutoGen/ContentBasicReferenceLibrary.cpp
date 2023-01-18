
#include "AutoGen/ContentBasicReferenceLibrary.h"

#include "CoreMinimal.h"


FString UContentBasicReferenceLibrary::ContentBasicReferenceToJsonString(const UContentBasicReference* Serializable, const bool Pretty)
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

UContentBasicReference* UContentBasicReferenceLibrary::Make(FString ContentPrefix, FString Visibility, EContentType Type, UObject* Outer)
{
	auto Serializable = NewObject<UContentBasicReference>(Outer);
	Serializable->ContentPrefix = ContentPrefix;
	Serializable->Visibility = Visibility;
	Serializable->Type = Type;
	
	return Serializable;
}

void UContentBasicReferenceLibrary::Break(const UContentBasicReference* Serializable, FString& ContentPrefix, FString& Visibility, EContentType& Type)
{
	ContentPrefix = Serializable->ContentPrefix;
	Visibility = Serializable->Visibility;
	Type = Serializable->Type;
		
}

