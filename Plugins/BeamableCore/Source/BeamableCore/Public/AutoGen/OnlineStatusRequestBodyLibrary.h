#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/OnlineStatusRequestBody.h"

#include "OnlineStatusRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOnlineStatusRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="OnlineStatusRequestBody To JSON String")
	static FString OnlineStatusRequestBodyToJsonString(const UOnlineStatusRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make OnlineStatusRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UOnlineStatusRequestBody* Make(FString PlayerIds, int64 IntervalSecs, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Break OnlineStatusRequestBody", meta=(NativeBreakFunc))
	static void Break(const UOnlineStatusRequestBody* Serializable, FString& PlayerIds, int64& IntervalSecs);
};