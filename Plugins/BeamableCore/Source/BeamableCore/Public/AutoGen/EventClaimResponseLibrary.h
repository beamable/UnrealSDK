
#pragma once

#include "CoreMinimal.h"
#include "EventClaimResponse.h"

#include "EventClaimResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventClaimResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventClaimResponse To JSON String")
	static FString EventClaimResponseToJsonString(const UEventClaimResponse* Serializable, const bool Pretty);		
};