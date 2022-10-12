
#pragma once

#include "CoreMinimal.h"
#include "PASlowQuery.h"

#include "PASlowQueryLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPASlowQueryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PASlowQuery To JSON String")
	static FString PASlowQueryToJsonString(const UPASlowQuery* Serializable, const bool Pretty);		
};