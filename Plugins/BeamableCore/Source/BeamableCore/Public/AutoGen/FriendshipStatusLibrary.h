#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/FriendshipStatus.h"

#include "FriendshipStatusLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UFriendshipStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Friends|4 - Json", DisplayName="FriendshipStatus To JSON String")
	static FString FriendshipStatusToJsonString(const UFriendshipStatus* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|3 - Backend", DisplayName="Make FriendshipStatus", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UFriendshipStatus* Make(bool bIsBlocked, FBeamGamerTag FriendId, FBeamGamerTag PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|3 - Backend", DisplayName="Break FriendshipStatus", meta=(NativeBreakFunc))
	static void Break(const UFriendshipStatus* Serializable, bool& bIsBlocked, FBeamGamerTag& FriendId, FBeamGamerTag& PlayerId);
};