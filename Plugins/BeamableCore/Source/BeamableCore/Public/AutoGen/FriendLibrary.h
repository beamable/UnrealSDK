#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Friend.h"

#include "FriendLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UFriendLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - Friend To JSON String")
	static FString FriendToJsonString(const UFriend* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make Friend", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UFriend* Make(FBeamGamerTag PlayerId, EFriendSource Source, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break Friend", meta=(NativeBreakFunc))
	static void Break(const UFriend* Serializable, FBeamGamerTag& PlayerId, EFriendSource& Source);
};