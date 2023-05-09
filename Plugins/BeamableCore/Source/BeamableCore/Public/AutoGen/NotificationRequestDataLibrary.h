#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/NotificationRequestData.h"

#include "NotificationRequestDataLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UNotificationRequestDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - NotificationRequestData To JSON String")
	static FString NotificationRequestDataToJsonString(const UNotificationRequestData* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make NotificationRequestData", meta=(DefaultToSelf="Outer", AdvancedDisplay="Channel, MessageKey, Context, Shard, MessageFull, MessageParams, Meta, Outer", NativeMakeFunc))
	static UNotificationRequestData* Make(FOptionalString Channel, FOptionalString MessageKey, FOptionalString Context, FOptionalString Shard, FOptionalString MessageFull, FOptionalArrayOfString MessageParams, FOptionalMapOfString Meta, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break NotificationRequestData", meta=(NativeBreakFunc))
	static void Break(const UNotificationRequestData* Serializable, FOptionalString& Channel, FOptionalString& MessageKey, FOptionalString& Context, FOptionalString& Shard, FOptionalString& MessageFull, FOptionalArrayOfString& MessageParams, FOptionalMapOfString& Meta);
};