
#pragma once

#include "CoreMinimal.h"
#include "UpdateListingCooldownRequestBody.h"

#include "UpdateListingCooldownRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UUpdateListingCooldownRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize UpdateListingCooldownRequestBody To JSON String")
	static FString UpdateListingCooldownRequestBodyToJsonString(const UUpdateListingCooldownRequestBody* Serializable, const bool Pretty);		
};