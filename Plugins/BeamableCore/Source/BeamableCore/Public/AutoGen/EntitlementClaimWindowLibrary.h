
#pragma once

#include "CoreMinimal.h"
#include "EntitlementClaimWindow.h"

#include "EntitlementClaimWindowLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEntitlementClaimWindowLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EntitlementClaimWindow To JSON String")
	static FString EntitlementClaimWindowToJsonString(const UEntitlementClaimWindow* Serializable, const bool Pretty);		
};