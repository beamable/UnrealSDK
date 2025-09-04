#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicServiceLimits.h"

#include "RealmsBasicServiceLimitsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicServiceLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicServiceLimits To JSON String")
	static FString RealmsBasicServiceLimitsToJsonString(const URealmsBasicServiceLimits* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicServiceLimits", meta=(DefaultToSelf="Outer", AdvancedDisplay="Beamo, Content, Gateway, Outer", NativeMakeFunc))
	static URealmsBasicServiceLimits* Make(FOptionalRealmsBasicBeamoLimits Beamo, FOptionalContentLimits Content, FOptionalGatewayLimits Gateway, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicServiceLimits", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicServiceLimits* Serializable, FOptionalRealmsBasicBeamoLimits& Beamo, FOptionalContentLimits& Content, FOptionalGatewayLimits& Gateway);
};