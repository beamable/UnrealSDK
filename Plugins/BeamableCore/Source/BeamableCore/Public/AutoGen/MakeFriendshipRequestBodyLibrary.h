#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MakeFriendshipRequestBody.h"

#include "MakeFriendshipRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMakeFriendshipRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Json", DisplayName="MakeFriendshipRequestBody To JSON String")
	static FString MakeFriendshipRequestBodyToJsonString(const UMakeFriendshipRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make MakeFriendshipRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMakeFriendshipRequestBody* Make(FBeamGamerTag GamerTag, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Break MakeFriendshipRequestBody", meta=(NativeBreakFunc))
	static void Break(const UMakeFriendshipRequestBody* Serializable, FBeamGamerTag& GamerTag);
};