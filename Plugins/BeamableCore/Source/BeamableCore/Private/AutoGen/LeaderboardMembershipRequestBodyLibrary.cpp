
#include "BeamableCore/Public/AutoGen/LeaderboardMembershipRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardMembershipRequestBodyLibrary::LeaderboardMembershipRequestBodyToJsonString(const ULeaderboardMembershipRequestBody* Serializable, const bool Pretty)
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

ULeaderboardMembershipRequestBody* ULeaderboardMembershipRequestBodyLibrary::Make(int64 PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardMembershipRequestBody>(Outer);
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void ULeaderboardMembershipRequestBodyLibrary::Break(const ULeaderboardMembershipRequestBody* Serializable, int64& PlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
	}
		
}

