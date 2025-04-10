#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SendFriendRequestBody.h"

#include "SendFriendRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USendFriendRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Json", DisplayName="SendFriendRequestBody To JSON String")
	static FString SendFriendRequestBodyToJsonString(const USendFriendRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make SendFriendRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USendFriendRequestBody* Make(FBeamGamerTag GamerTag, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Break SendFriendRequestBody", meta=(NativeBreakFunc))
	static void Break(const USendFriendRequestBody* Serializable, FBeamGamerTag& GamerTag);
};