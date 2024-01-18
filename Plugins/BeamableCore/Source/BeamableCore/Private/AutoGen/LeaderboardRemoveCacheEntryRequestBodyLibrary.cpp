
#include "BeamableCore/Public/AutoGen/LeaderboardRemoveCacheEntryRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString ULeaderboardRemoveCacheEntryRequestBodyLibrary::LeaderboardRemoveCacheEntryRequestBodyToJsonString(const ULeaderboardRemoveCacheEntryRequestBody* Serializable, const bool Pretty)
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

ULeaderboardRemoveCacheEntryRequestBody* ULeaderboardRemoveCacheEntryRequestBodyLibrary::Make(int64 PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardRemoveCacheEntryRequestBody>(Outer);
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void ULeaderboardRemoveCacheEntryRequestBodyLibrary::Break(const ULeaderboardRemoveCacheEntryRequestBody* Serializable, int64& PlayerId)
{
	PlayerId = Serializable->PlayerId;
		
}

