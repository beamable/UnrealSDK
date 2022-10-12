
#pragma once

#include "CoreMinimal.h"
#include "ActiveListingResponse.h"

#include "ActiveListingResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UActiveListingResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ActiveListingResponse To JSON String")
	static FString ActiveListingResponseToJsonString(const UActiveListingResponse* Serializable, const bool Pretty);		
};