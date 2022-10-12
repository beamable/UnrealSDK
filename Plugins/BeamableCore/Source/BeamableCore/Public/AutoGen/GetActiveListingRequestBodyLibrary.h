
#pragma once

#include "CoreMinimal.h"
#include "GetActiveListingRequestBody.h"

#include "GetActiveListingRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetActiveListingRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetActiveListingRequestBody To JSON String")
	static FString GetActiveListingRequestBodyToJsonString(const UGetActiveListingRequestBody* Serializable, const bool Pretty);		
};