#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardMembershipRequestBody.h"

#include "LeaderboardMembershipRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardMembershipRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LeaderboardMembershipRequestBody To JSON String")
	static FString LeaderboardMembershipRequestBodyToJsonString(const ULeaderboardMembershipRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LeaderboardMembershipRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULeaderboardMembershipRequestBody* Make(int64 PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LeaderboardMembershipRequestBody", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardMembershipRequestBody* Serializable, int64& PlayerId);
};