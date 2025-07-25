
#include "BeamableCore/Public/AutoGen/LeaderboardGetRanksRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardGetRanksRequestBodyLibrary::LeaderboardGetRanksRequestBodyToJsonString(const ULeaderboardGetRanksRequestBody* Serializable, const bool Pretty)
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

ULeaderboardGetRanksRequestBody* ULeaderboardGetRanksRequestBodyLibrary::Make(FString Ids, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardGetRanksRequestBody>(Outer);
	Serializable->Ids = Ids;
	
	return Serializable;
}

void ULeaderboardGetRanksRequestBodyLibrary::Break(const ULeaderboardGetRanksRequestBody* Serializable, FString& Ids)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Ids = Serializable->Ids;
	}
		
}

