#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/OnlineStatusQuery.h"

#include "OnlineStatusQueryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOnlineStatusQueryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - OnlineStatusQuery To JSON String")
	static FString OnlineStatusQueryToJsonString(const UOnlineStatusQuery* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make OnlineStatusQuery", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerIds, Outer", NativeMakeFunc))
	static UOnlineStatusQuery* Make(FOptionalArrayOfString PlayerIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break OnlineStatusQuery", meta=(NativeBreakFunc))
	static void Break(const UOnlineStatusQuery* Serializable, FOptionalArrayOfString& PlayerIds);
};