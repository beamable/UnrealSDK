
#pragma once

#include "CoreMinimal.h"
#include "DataPoint.h"

#include "DataPointLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UDataPointLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize DataPoint To JSON String")
	static FString DataPointToJsonString(const UDataPoint* Serializable, const bool Pretty);		
};