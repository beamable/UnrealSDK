#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/WebSocketConfiguration.h"

#include "WebSocketConfigurationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UWebSocketConfigurationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - WebSocketConfiguration To JSON String")
	static FString WebSocketConfigurationToJsonString(const UWebSocketConfiguration* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make WebSocketConfiguration", meta=(DefaultToSelf="Outer", AdvancedDisplay="Uri, Outer", NativeMakeFunc))
	static UWebSocketConfiguration* Make(FString Provider, FOptionalString Uri, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break WebSocketConfiguration", meta=(NativeBreakFunc))
	static void Break(const UWebSocketConfiguration* Serializable, FString& Provider, FOptionalString& Uri);
};