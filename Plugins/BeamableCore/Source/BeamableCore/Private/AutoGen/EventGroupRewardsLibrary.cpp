
#include "BeamableCore/Public/AutoGen/EventGroupRewardsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventGroupRewardsLibrary::EventGroupRewardsToJsonString(const UEventGroupRewards* Serializable, const bool Pretty)
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

UEventGroupRewards* UEventGroupRewardsLibrary::Make(FOptionalArrayOfEventRewardContent ScoreRewards, UObject* Outer)
{
	auto Serializable = NewObject<UEventGroupRewards>(Outer);
	Serializable->ScoreRewards = ScoreRewards;
	
	return Serializable;
}

void UEventGroupRewardsLibrary::Break(const UEventGroupRewards* Serializable, FOptionalArrayOfEventRewardContent& ScoreRewards)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ScoreRewards = Serializable->ScoreRewards;
	}
		
}

