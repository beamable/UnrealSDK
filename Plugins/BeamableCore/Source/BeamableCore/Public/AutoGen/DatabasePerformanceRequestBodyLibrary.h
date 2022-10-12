
#pragma once

#include "CoreMinimal.h"
#include "DatabasePerformanceRequestBody.h"

#include "DatabasePerformanceRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UDatabasePerformanceRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize DatabasePerformanceRequestBody To JSON String")
	static FString DatabasePerformanceRequestBodyToJsonString(const UDatabasePerformanceRequestBody* Serializable, const bool Pretty);		
};