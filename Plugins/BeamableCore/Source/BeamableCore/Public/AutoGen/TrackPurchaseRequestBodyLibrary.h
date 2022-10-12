
#pragma once

#include "CoreMinimal.h"
#include "TrackPurchaseRequestBody.h"

#include "TrackPurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UTrackPurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize TrackPurchaseRequestBody To JSON String")
	static FString TrackPurchaseRequestBodyToJsonString(const UTrackPurchaseRequestBody* Serializable, const bool Pretty);		
};