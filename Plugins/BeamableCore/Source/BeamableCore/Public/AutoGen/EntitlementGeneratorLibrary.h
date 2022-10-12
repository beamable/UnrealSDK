
#pragma once

#include "CoreMinimal.h"
#include "EntitlementGenerator.h"

#include "EntitlementGeneratorLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEntitlementGeneratorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EntitlementGenerator To JSON String")
	static FString EntitlementGeneratorToJsonString(const UEntitlementGenerator* Serializable, const bool Pretty);		
};