
#pragma once

#include "CoreMinimal.h"
#include "OfferRequirement.h"

#include "OfferRequirementLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UOfferRequirementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize OfferRequirement To JSON String")
	static FString OfferRequirementToJsonString(const UOfferRequirement* Serializable, const bool Pretty);		
};