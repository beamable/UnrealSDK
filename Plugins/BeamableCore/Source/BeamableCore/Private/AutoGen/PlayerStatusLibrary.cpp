
#include "BeamableCore/Public/AutoGen/PlayerStatusLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPlayerStatusLibrary::PlayerStatusToJsonString(const UPlayerStatus* Serializable, const bool Pretty)
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

UPlayerStatus* UPlayerStatusLibrary::Make(int32 LastUpdateCycle, FString TournamentId, int32 Stage, int32 Tier, int64 PlayerId, FString ContentId, TArray<UTournamentCurrencyReward*> UnclaimedRewards, FOptionalInt64 GroupId, UObject* Outer)
{
	auto Serializable = NewObject<UPlayerStatus>(Outer);
	Serializable->LastUpdateCycle = LastUpdateCycle;
	Serializable->TournamentId = TournamentId;
	Serializable->Stage = Stage;
	Serializable->Tier = Tier;
	Serializable->PlayerId = PlayerId;
	Serializable->ContentId = ContentId;
	Serializable->UnclaimedRewards = UnclaimedRewards;
	Serializable->GroupId = GroupId;
	
	return Serializable;
}

void UPlayerStatusLibrary::Break(const UPlayerStatus* Serializable, int32& LastUpdateCycle, FString& TournamentId, int32& Stage, int32& Tier, int64& PlayerId, FString& ContentId, TArray<UTournamentCurrencyReward*>& UnclaimedRewards, FOptionalInt64& GroupId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		LastUpdateCycle = Serializable->LastUpdateCycle;
		TournamentId = Serializable->TournamentId;
		Stage = Serializable->Stage;
		Tier = Serializable->Tier;
		PlayerId = Serializable->PlayerId;
		ContentId = Serializable->ContentId;
		UnclaimedRewards = Serializable->UnclaimedRewards;
		GroupId = Serializable->GroupId;
	}
		
}

