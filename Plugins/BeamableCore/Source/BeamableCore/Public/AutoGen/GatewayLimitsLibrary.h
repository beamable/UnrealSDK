#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GatewayLimits.h"

#include "GatewayLimitsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGatewayLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="GatewayLimits To JSON String")
	static FString GatewayLimitsToJsonString(const UGatewayLimits* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make GatewayLimits", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGatewayLimits* Make(int32 MaxConcurrentRequests, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break GatewayLimits", meta=(NativeBreakFunc))
	static void Break(const UGatewayLimits* Serializable, int32& MaxConcurrentRequests);
};