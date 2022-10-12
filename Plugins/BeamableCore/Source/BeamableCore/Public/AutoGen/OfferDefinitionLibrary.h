
#pragma once

#include "CoreMinimal.h"
#include "OfferDefinition.h"

#include "OfferDefinitionLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UOfferDefinitionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize OfferDefinition To JSON String")
	static FString OfferDefinitionToJsonString(const UOfferDefinition* Serializable, const bool Pretty);		
};