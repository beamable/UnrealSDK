
#pragma once

#include "CoreMinimal.h"
#include "StatRequestBody.h"

#include "StatRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UStatRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize StatRequestBody To JSON String")
	static FString StatRequestBodyToJsonString(const UStatRequestBody* Serializable, const bool Pretty);		
};