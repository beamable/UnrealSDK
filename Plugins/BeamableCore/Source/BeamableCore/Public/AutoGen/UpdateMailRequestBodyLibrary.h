
#pragma once

#include "CoreMinimal.h"
#include "UpdateMailRequestBody.h"

#include "UpdateMailRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UUpdateMailRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize UpdateMailRequestBody To JSON String")
	static FString UpdateMailRequestBodyToJsonString(const UUpdateMailRequestBody* Serializable, const bool Pretty);		
};