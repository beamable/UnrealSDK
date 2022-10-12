
#pragma once

#include "CoreMinimal.h"
#include "SendMailRequestBody.h"

#include "SendMailRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USendMailRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SendMailRequestBody To JSON String")
	static FString SendMailRequestBodyToJsonString(const USendMailRequestBody* Serializable, const bool Pretty);		
};