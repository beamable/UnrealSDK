#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/NotificationRequestBody.h"

#include "NotificationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UNotificationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Notification|Utils|Json", DisplayName="NotificationRequestBody To JSON String")
	static FString NotificationRequestBodyToJsonString(const UNotificationRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Notification|Utils|Make/Break", DisplayName="Make NotificationRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bUseSignalWhenPossible, CustomChannelSuffix, Dbid, Dbids, Outer", NativeMakeFunc))
	static UNotificationRequestBody* Make(UNotificationRequestData* Payload, FOptionalBool bUseSignalWhenPossible, FOptionalString CustomChannelSuffix, FOptionalInt64 Dbid, FOptionalArrayOfInt64 Dbids, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Notification|Utils|Make/Break", DisplayName="Break NotificationRequestBody", meta=(NativeBreakFunc))
	static void Break(const UNotificationRequestBody* Serializable, UNotificationRequestData*& Payload, FOptionalBool& bUseSignalWhenPossible, FOptionalString& CustomChannelSuffix, FOptionalInt64& Dbid, FOptionalArrayOfInt64& Dbids);
};