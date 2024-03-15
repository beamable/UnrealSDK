
#include "BeamableCore/Public/AutoGen/LeaderboardListRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString ULeaderboardListRequestBodyLibrary::LeaderboardListRequestBodyToJsonString(const ULeaderboardListRequestBody* Serializable, const bool Pretty)
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

ULeaderboardListRequestBody* ULeaderboardListRequestBodyLibrary::Make(FOptionalInt32 Skip, FOptionalInt32 Limit, FOptionalString Prefix, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardListRequestBody>(Outer);
	Serializable->Skip = Skip;
	Serializable->Limit = Limit;
	Serializable->Prefix = Prefix;
	
	return Serializable;
}

void ULeaderboardListRequestBodyLibrary::Break(const ULeaderboardListRequestBody* Serializable, FOptionalInt32& Skip, FOptionalInt32& Limit, FOptionalString& Prefix)
{
	Skip = Serializable->Skip;
	Limit = Serializable->Limit;
	Prefix = Serializable->Prefix;
		
}

