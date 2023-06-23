
#include "BeamableCore/Public/AutoGen/OnlineStatusQueryLibrary.h"

#include "CoreMinimal.h"


FString UOnlineStatusQueryLibrary::OnlineStatusQueryToJsonString(const UOnlineStatusQuery* Serializable, const bool Pretty)
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

UOnlineStatusQuery* UOnlineStatusQueryLibrary::Make(FOptionalBool bToManyRequests, FOptionalArrayOfString PlayerIds, UObject* Outer)
{
	auto Serializable = NewObject<UOnlineStatusQuery>(Outer);
	Serializable->bToManyRequests = bToManyRequests;
	Serializable->PlayerIds = PlayerIds;
	
	return Serializable;
}

void UOnlineStatusQueryLibrary::Break(const UOnlineStatusQuery* Serializable, FOptionalBool& bToManyRequests, FOptionalArrayOfString& PlayerIds)
{
	bToManyRequests = Serializable->bToManyRequests;
	PlayerIds = Serializable->PlayerIds;
		
}

