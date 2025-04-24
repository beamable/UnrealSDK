#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardRemoveEntryRequestBody.h"

#include "LeaderboardRemoveEntryRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardRemoveEntryRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Json", DisplayName="LeaderboardRemoveEntryRequestBody To JSON String")
	static FString LeaderboardRemoveEntryRequestBodyToJsonString(const ULeaderboardRemoveEntryRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make LeaderboardRemoveEntryRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULeaderboardRemoveEntryRequestBody* Make(int64 Id, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Break LeaderboardRemoveEntryRequestBody", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardRemoveEntryRequestBody* Serializable, int64& Id);
};