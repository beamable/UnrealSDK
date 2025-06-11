#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceLimits.h"

#include "ServiceLimitsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="ServiceLimits To JSON String")
	static FString ServiceLimitsToJsonString(const UServiceLimits* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make ServiceLimits", meta=(DefaultToSelf="Outer", AdvancedDisplay="Beamo, Content, Gateway, Outer", NativeMakeFunc))
	static UServiceLimits* Make(FOptionalBeamoLimits Beamo, FOptionalContentLimits Content, FOptionalGatewayLimits Gateway, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break ServiceLimits", meta=(NativeBreakFunc))
	static void Break(const UServiceLimits* Serializable, FOptionalBeamoLimits& Beamo, FOptionalContentLimits& Content, FOptionalGatewayLimits& Gateway);
};