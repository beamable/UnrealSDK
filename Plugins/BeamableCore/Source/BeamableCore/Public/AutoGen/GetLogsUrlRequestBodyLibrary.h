
#pragma once

#include "CoreMinimal.h"
#include "GetLogsUrlRequestBody.h"

#include "GetLogsUrlRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetLogsUrlRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetLogsUrlRequestBody To JSON String")
	static FString GetLogsUrlRequestBodyToJsonString(const UGetLogsUrlRequestBody* Serializable, const bool Pretty);		
};