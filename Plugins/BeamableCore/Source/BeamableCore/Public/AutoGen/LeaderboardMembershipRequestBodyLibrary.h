#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardMembershipRequestBody.h"

#include "LeaderboardMembershipRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardMembershipRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Json", DisplayName="LeaderboardMembershipRequestBody To JSON String")
	static FString LeaderboardMembershipRequestBodyToJsonString(const ULeaderboardMembershipRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make LeaderboardMembershipRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULeaderboardMembershipRequestBody* Make(int64 PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Break LeaderboardMembershipRequestBody", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardMembershipRequestBody* Serializable, int64& PlayerId);
};