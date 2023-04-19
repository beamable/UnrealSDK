
#include "BeamableCore/Public/AutoGen/SendMessageResponseLibrary.h"

#include "CoreMinimal.h"


FString USendMessageResponseLibrary::SendMessageResponseToJsonString(const USendMessageResponse* Serializable, const bool Pretty)
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

USendMessageResponse* USendMessageResponseLibrary::Make(UChatV2ObjectMessage* Message, UObject* Outer)
{
	auto Serializable = NewObject<USendMessageResponse>(Outer);
	Serializable->Message = Message;
	
	return Serializable;
}

void USendMessageResponseLibrary::Break(const USendMessageResponse* Serializable, UChatV2ObjectMessage*& Message)
{
	Message = Serializable->Message;
		
}

