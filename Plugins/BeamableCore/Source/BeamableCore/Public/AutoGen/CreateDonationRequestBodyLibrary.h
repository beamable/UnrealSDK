
#pragma once

#include "CoreMinimal.h"
#include "CreateDonationRequestBody.h"

#include "CreateDonationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCreateDonationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CreateDonationRequestBody To JSON String")
	static FString CreateDonationRequestBodyToJsonString(const UCreateDonationRequestBody* Serializable, const bool Pretty);		
};