
#include "BeamableCore/Public/AutoGen/LeaderboardMembershipResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardMembershipResponseLibrary::LeaderboardMembershipResponseToJsonString(const ULeaderboardMembershipResponse* Serializable, const bool Pretty)
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

ULeaderboardMembershipResponse* ULeaderboardMembershipResponseLibrary::Make(bool bResult, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardMembershipResponse>(Outer);
	Serializable->bResult = bResult;
	
	return Serializable;
}

void ULeaderboardMembershipResponseLibrary::Break(const ULeaderboardMembershipResponse* Serializable, bool& bResult)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bResult = Serializable->bResult;
	}
		
}

