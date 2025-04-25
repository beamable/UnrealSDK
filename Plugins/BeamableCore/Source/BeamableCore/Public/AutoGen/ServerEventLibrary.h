#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServerEvent.h"

#include "ServerEventLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServerEventLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Notification|Utils|Json", DisplayName="ServerEvent To JSON String")
	static FString ServerEventToJsonString(const UServerEvent* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Notification|Utils|Make/Break", DisplayName="Make ServerEvent", meta=(DefaultToSelf="Outer", AdvancedDisplay="Payload, Outer", NativeMakeFunc))
	static UServerEvent* Make(FString Event, bool bToAll, FOptionalString Payload, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Notification|Utils|Make/Break", DisplayName="Break ServerEvent", meta=(NativeBreakFunc))
	static void Break(const UServerEvent* Serializable, FString& Event, bool& bToAll, FOptionalString& Payload);
};