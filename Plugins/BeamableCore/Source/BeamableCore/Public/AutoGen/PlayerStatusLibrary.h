#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PlayerStatus.h"

#include "PlayerStatusLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPlayerStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - PlayerStatus To JSON String")
	static FString PlayerStatusToJsonString(const UPlayerStatus* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make PlayerStatus", meta=(DefaultToSelf="Outer", AdvancedDisplay="GroupId, Outer", NativeMakeFunc))
	static UPlayerStatus* Make(int32 LastUpdateCycle, FString TournamentId, int32 Stage, int32 Tier, int64 PlayerId, FString ContentId, TArray<UTournamentCurrencyReward*> UnclaimedRewards, FOptionalInt64 GroupId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break PlayerStatus", meta=(NativeBreakFunc))
	static void Break(const UPlayerStatus* Serializable, int32& LastUpdateCycle, FString& TournamentId, int32& Stage, int32& Tier, int64& PlayerId, FString& ContentId, TArray<UTournamentCurrencyReward*>& UnclaimedRewards, FOptionalInt64& GroupId);
};