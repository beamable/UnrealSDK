

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalMapOfDonationRequestBody.h"

#include "OptionalMapOfDonationRequestBodyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalMapOfDonationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalMapOfDonationRequestBody MakeOptionalMapOfDonationRequestBody(TMap<FString, UDonationRequestBody*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TMap<FString, UDonationRequestBody*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalMapOfDonationRequestBody Conv_OptionalMapOfDonationRequestBodyFromValue(TMap<FString, UDonationRequestBody*> Value);
};
