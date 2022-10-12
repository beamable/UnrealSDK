
#pragma once

#include "CoreMinimal.h"
#include "SendMessageRequestBody.h"

#include "SendMessageRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USendMessageRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SendMessageRequestBody To JSON String")
	static FString SendMessageRequestBodyToJsonString(const USendMessageRequestBody* Serializable, const bool Pretty);		
};