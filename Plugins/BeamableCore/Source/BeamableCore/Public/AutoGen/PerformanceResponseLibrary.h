
#pragma once

#include "CoreMinimal.h"
#include "PerformanceResponse.h"

#include "PerformanceResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPerformanceResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PerformanceResponse To JSON String")
	static FString PerformanceResponseToJsonString(const UPerformanceResponse* Serializable, const bool Pretty);		
};