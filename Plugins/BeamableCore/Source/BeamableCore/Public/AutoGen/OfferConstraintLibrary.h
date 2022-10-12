
#pragma once

#include "CoreMinimal.h"
#include "OfferConstraint.h"

#include "OfferConstraintLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UOfferConstraintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize OfferConstraint To JSON String")
	static FString OfferConstraintToJsonString(const UOfferConstraint* Serializable, const bool Pretty);		
};