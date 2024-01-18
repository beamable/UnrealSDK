
#include "BeamableCore/Public/AutoGen/EventApplyRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UEventApplyRequestBodyLibrary::EventApplyRequestBodyToJsonString(const UEventApplyRequestBody* Serializable, const bool Pretty)
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

UEventApplyRequestBody* UEventApplyRequestBodyLibrary::Make(UEvent* Content, UObject* Outer)
{
	auto Serializable = NewObject<UEventApplyRequestBody>(Outer);
	Serializable->Content = Content;
	
	return Serializable;
}

void UEventApplyRequestBodyLibrary::Break(const UEventApplyRequestBody* Serializable, UEvent*& Content)
{
	Content = Serializable->Content;
		
}

