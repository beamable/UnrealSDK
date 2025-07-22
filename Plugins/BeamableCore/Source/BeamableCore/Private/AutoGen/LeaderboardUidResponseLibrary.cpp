
#include "BeamableCore/Public/AutoGen/LeaderboardUidResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardUidResponseLibrary::LeaderboardUidResponseToJsonString(const ULeaderboardUidResponse* Serializable, const bool Pretty)
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

ULeaderboardUidResponse* ULeaderboardUidResponseLibrary::Make(int64 Id, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardUidResponse>(Outer);
	Serializable->Id = Id;
	
	return Serializable;
}

void ULeaderboardUidResponseLibrary::Break(const ULeaderboardUidResponse* Serializable, int64& Id)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
	}
		
}

