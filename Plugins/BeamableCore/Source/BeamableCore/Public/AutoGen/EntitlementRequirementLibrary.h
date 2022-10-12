
#pragma once

#include "CoreMinimal.h"
#include "EntitlementRequirement.h"

#include "EntitlementRequirementLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEntitlementRequirementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EntitlementRequirement To JSON String")
	static FString EntitlementRequirementToJsonString(const UEntitlementRequirement* Serializable, const bool Pretty);		
};