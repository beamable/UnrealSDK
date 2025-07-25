
#include "BeamableCore/Public/AutoGen/AdminPlayerStatusLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAdminPlayerStatusLibrary::AdminPlayerStatusToJsonString(const UAdminPlayerStatus* Serializable, const bool Pretty)
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

UAdminPlayerStatus* UAdminPlayerStatusLibrary::Make(FString TournamentId, int32 Stage, int32 Tier, int32 Rank, double Score, int64 PlayerId, FString ContentId, int64 NextCycleStartMs, TArray<UTournamentCurrencyReward*> UnclaimedRewards, UObject* Outer)
{
	auto Serializable = NewObject<UAdminPlayerStatus>(Outer);
	Serializable->TournamentId = TournamentId;
	Serializable->Stage = Stage;
	Serializable->Tier = Tier;
	Serializable->Rank = Rank;
	Serializable->Score = Score;
	Serializable->PlayerId = PlayerId;
	Serializable->ContentId = ContentId;
	Serializable->NextCycleStartMs = NextCycleStartMs;
	Serializable->UnclaimedRewards = UnclaimedRewards;
	
	return Serializable;
}

void UAdminPlayerStatusLibrary::Break(const UAdminPlayerStatus* Serializable, FString& TournamentId, int32& Stage, int32& Tier, int32& Rank, double& Score, int64& PlayerId, FString& ContentId, int64& NextCycleStartMs, TArray<UTournamentCurrencyReward*>& UnclaimedRewards)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		TournamentId = Serializable->TournamentId;
		Stage = Serializable->Stage;
		Tier = Serializable->Tier;
		Rank = Serializable->Rank;
		Score = Serializable->Score;
		PlayerId = Serializable->PlayerId;
		ContentId = Serializable->ContentId;
		NextCycleStartMs = Serializable->NextCycleStartMs;
		UnclaimedRewards = Serializable->UnclaimedRewards;
	}
		
}

