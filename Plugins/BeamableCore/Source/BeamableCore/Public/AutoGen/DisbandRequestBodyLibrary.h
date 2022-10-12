
#pragma once

#include "CoreMinimal.h"
#include "DisbandRequestBody.h"

#include "DisbandRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UDisbandRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize DisbandRequestBody To JSON String")
	static FString DisbandRequestBodyToJsonString(const UDisbandRequestBody* Serializable, const bool Pretty);		
};