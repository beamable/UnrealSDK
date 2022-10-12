
#pragma once

#include "CoreMinimal.h"
#include "ResultResponse.h"

#include "ResultResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UResultResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ResultResponse To JSON String")
	static FString ResultResponseToJsonString(const UResultResponse* Serializable, const bool Pretty);		
};