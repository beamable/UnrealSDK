
#include "AutoGen/SendFriendRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString USendFriendRequestBodyLibrary::SendFriendRequestBodyToJsonString(const USendFriendRequestBody* Serializable, const bool Pretty)
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

USendFriendRequestBody* USendFriendRequestBodyLibrary::Make(int64 GamerTag, UObject* Outer)
{
	auto Serializable = NewObject<USendFriendRequestBody>(Outer);
	Serializable->GamerTag = GamerTag;
	
	return Serializable;
}

void USendFriendRequestBodyLibrary::Break(const USendFriendRequestBody* Serializable, int64& GamerTag)
{
	GamerTag = Serializable->GamerTag;
		
}

