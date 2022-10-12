
#pragma once

#include "CoreMinimal.h"
#include "DonationRequestBody.h"

#include "DonationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UDonationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize DonationRequestBody To JSON String")
	static FString DonationRequestBodyToJsonString(const UDonationRequestBody* Serializable, const bool Pretty);		
};