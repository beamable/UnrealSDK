
#pragma once

#include "CoreMinimal.h"
#include "SetContentRequestBody.h"

#include "SetContentRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USetContentRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SetContentRequestBody To JSON String")
	static FString SetContentRequestBodyToJsonString(const USetContentRequestBody* Serializable, const bool Pretty);		
};