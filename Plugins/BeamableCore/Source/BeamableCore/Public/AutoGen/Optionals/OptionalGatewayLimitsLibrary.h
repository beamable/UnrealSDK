

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalGatewayLimits.h"

#include "OptionalGatewayLimitsLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalGatewayLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalGatewayLimits MakeOptionalGatewayLimits(UGatewayLimits* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GatewayLimits To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalGatewayLimits Conv_OptionalGatewayLimitsFromValue(UGatewayLimits* Value);
};
