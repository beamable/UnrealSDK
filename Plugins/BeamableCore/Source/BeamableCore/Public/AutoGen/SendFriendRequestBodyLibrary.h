#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SendFriendRequestBody.h"

#include "SendFriendRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USendFriendRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SendFriendRequestBody To JSON String")
	static FString SendFriendRequestBodyToJsonString(const USendFriendRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SendFriendRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USendFriendRequestBody* Make(FBeamGamerTag GamerTag, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SendFriendRequestBody", meta=(NativeBreakFunc))
	static void Break(const USendFriendRequestBody* Serializable, FBeamGamerTag& GamerTag);
};