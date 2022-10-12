
#pragma once

#include "CoreMinimal.h"
#include "CreateLaunchMessageRequestBody.h"

#include "CreateLaunchMessageRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCreateLaunchMessageRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CreateLaunchMessageRequestBody To JSON String")
	static FString CreateLaunchMessageRequestBodyToJsonString(const UCreateLaunchMessageRequestBody* Serializable, const bool Pretty);		
};