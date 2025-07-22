
#include "BeamableCore/Public/AutoGen/LeaderboardAssignmentInfoLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardAssignmentInfoLibrary::LeaderboardAssignmentInfoToJsonString(const ULeaderboardAssignmentInfo* Serializable, const bool Pretty)
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

ULeaderboardAssignmentInfo* ULeaderboardAssignmentInfoLibrary::Make(int64 PlayerId, FString LeaderboardId, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardAssignmentInfo>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->LeaderboardId = LeaderboardId;
	
	return Serializable;
}

void ULeaderboardAssignmentInfoLibrary::Break(const ULeaderboardAssignmentInfo* Serializable, int64& PlayerId, FString& LeaderboardId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		LeaderboardId = Serializable->LeaderboardId;
	}
		
}

