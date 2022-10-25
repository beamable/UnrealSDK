
#include "AutoGen/SendMessageRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString USendMessageRequestBodyLibrary::SendMessageRequestBodyToJsonString(const USendMessageRequestBody* Serializable, const bool Pretty)
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

USendMessageRequestBody* USendMessageRequestBodyLibrary::Make(FString RoomId, FString Content, UObject* Outer)
{
	auto Serializable = NewObject<USendMessageRequestBody>(Outer);
	Serializable->RoomId = RoomId;
	Serializable->Content = Content;
	
	return Serializable;
}

void USendMessageRequestBodyLibrary::Break(const USendMessageRequestBody* Serializable, FString& RoomId, FString& Content)
{
	RoomId = Serializable->RoomId;
	Content = Serializable->Content;
		
}

