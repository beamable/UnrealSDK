#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AdminPlayerStatus.h"

#include "AdminPlayerStatusLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAdminPlayerStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="AdminPlayerStatus To JSON String")
	static FString AdminPlayerStatusToJsonString(const UAdminPlayerStatus* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make AdminPlayerStatus", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAdminPlayerStatus* Make(FString TournamentId, int32 Stage, int32 Tier, int32 Rank, double Score, int64 PlayerId, FString ContentId, int64 NextCycleStartMs, TArray<UTournamentCurrencyReward*> UnclaimedRewards, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break AdminPlayerStatus", meta=(NativeBreakFunc))
	static void Break(const UAdminPlayerStatus* Serializable, FString& TournamentId, int32& Stage, int32& Tier, int32& Rank, double& Score, int64& PlayerId, FString& ContentId, int64& NextCycleStartMs, TArray<UTournamentCurrencyReward*>& UnclaimedRewards);
};