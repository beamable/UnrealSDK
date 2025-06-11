#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Friend.h"

#include "FriendLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UFriendLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Json", DisplayName="Friend To JSON String")
	static FString FriendToJsonString(const UFriend* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make Friend", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UFriend* Make(FBeamGamerTag PlayerId, EBeamFriendSource Source, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Break Friend", meta=(NativeBreakFunc))
	static void Break(const UFriend* Serializable, FBeamGamerTag& PlayerId, EBeamFriendSource& Source);
};