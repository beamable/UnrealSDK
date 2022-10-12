
#pragma once

#include "CoreMinimal.h"
#include "GatewayLimits.h"

#include "GatewayLimitsLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGatewayLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GatewayLimits To JSON String")
	static FString GatewayLimitsToJsonString(const UGatewayLimits* Serializable, const bool Pretty);		
};