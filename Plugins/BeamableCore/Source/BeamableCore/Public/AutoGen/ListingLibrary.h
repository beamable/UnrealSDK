
#pragma once

#include "CoreMinimal.h"
#include "Listing.h"

#include "ListingLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UListingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Listing To JSON String")
	static FString ListingToJsonString(const UListing* Serializable, const bool Pretty);		
};