#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceLimits.h"

#include "ServiceLimitsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ServiceLimits To JSON String")
	static FString ServiceLimitsToJsonString(const UServiceLimits* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ServiceLimits", meta=(DefaultToSelf="Outer", AdvancedDisplay="Beamo, Content, Gateway, Outer", NativeMakeFunc))
	static UServiceLimits* Make(FOptionalBeamoLimits Beamo, FOptionalContentLimits Content, FOptionalGatewayLimits Gateway, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ServiceLimits", meta=(NativeBreakFunc))
	static void Break(const UServiceLimits* Serializable, FOptionalBeamoLimits& Beamo, FOptionalContentLimits& Content, FOptionalGatewayLimits& Gateway);
};