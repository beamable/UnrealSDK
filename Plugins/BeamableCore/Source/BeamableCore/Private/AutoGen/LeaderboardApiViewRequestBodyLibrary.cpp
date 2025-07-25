
#include "BeamableCore/Public/AutoGen/LeaderboardApiViewRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardApiViewRequestBodyLibrary::LeaderboardApiViewRequestBodyToJsonString(const ULeaderboardApiViewRequestBody* Serializable, const bool Pretty)
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

ULeaderboardApiViewRequestBody* ULeaderboardApiViewRequestBodyLibrary::Make(FOptionalBool bFriends, FOptionalBool bGuild, FOptionalInt32 Max, FOptionalInt64 Focus, FOptionalInt32 From, FOptionalInt64 Outlier, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardApiViewRequestBody>(Outer);
	Serializable->bFriends = bFriends;
	Serializable->bGuild = bGuild;
	Serializable->Max = Max;
	Serializable->Focus = Focus;
	Serializable->From = From;
	Serializable->Outlier = Outlier;
	
	return Serializable;
}

void ULeaderboardApiViewRequestBodyLibrary::Break(const ULeaderboardApiViewRequestBody* Serializable, FOptionalBool& bFriends, FOptionalBool& bGuild, FOptionalInt32& Max, FOptionalInt64& Focus, FOptionalInt32& From, FOptionalInt64& Outlier)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bFriends = Serializable->bFriends;
		bGuild = Serializable->bGuild;
		Max = Serializable->Max;
		Focus = Serializable->Focus;
		From = Serializable->From;
		Outlier = Serializable->Outlier;
	}
		
}

