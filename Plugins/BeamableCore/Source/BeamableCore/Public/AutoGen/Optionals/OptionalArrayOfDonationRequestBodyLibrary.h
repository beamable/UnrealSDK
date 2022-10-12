

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfDonationRequestBody.h"

#include "OptionalArrayOfDonationRequestBodyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfDonationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfDonationRequestBody MakeOptionalArrayOfDonationRequestBody(TArray<UDonationRequestBody*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UDonationRequestBody*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfDonationRequestBody Conv_OptionalArrayOfDonationRequestBodyFromValue(TArray<UDonationRequestBody*> Value);
};
