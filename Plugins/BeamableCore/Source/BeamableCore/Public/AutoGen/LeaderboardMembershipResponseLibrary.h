#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardMembershipResponse.h"

#include "LeaderboardMembershipResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardMembershipResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LeaderboardMembershipResponse To JSON String")
	static FString LeaderboardMembershipResponseToJsonString(const ULeaderboardMembershipResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LeaderboardMembershipResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULeaderboardMembershipResponse* Make(bool bResult, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LeaderboardMembershipResponse", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardMembershipResponse* Serializable, bool& bResult);
};