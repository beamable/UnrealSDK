

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalEntitlementClaimWindow.h"

#include "OptionalEntitlementClaimWindowLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalEntitlementClaimWindowLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalEntitlementClaimWindow MakeOptionalEntitlementClaimWindow(UEntitlementClaimWindow* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "EntitlementClaimWindow To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalEntitlementClaimWindow Conv_OptionalEntitlementClaimWindowFromValue(UEntitlementClaimWindow* Value);
};
