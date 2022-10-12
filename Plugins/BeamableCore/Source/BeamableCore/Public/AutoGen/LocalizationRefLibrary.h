
#pragma once

#include "CoreMinimal.h"
#include "LocalizationRef.h"

#include "LocalizationRefLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULocalizationRefLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LocalizationRef To JSON String")
	static FString LocalizationRefToJsonString(const ULocalizationRef* Serializable, const bool Pretty);		
};