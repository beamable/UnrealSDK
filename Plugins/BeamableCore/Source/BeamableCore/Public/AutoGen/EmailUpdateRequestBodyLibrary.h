
#pragma once

#include "CoreMinimal.h"
#include "EmailUpdateRequestBody.h"

#include "EmailUpdateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEmailUpdateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EmailUpdateRequestBody To JSON String")
	static FString EmailUpdateRequestBodyToJsonString(const UEmailUpdateRequestBody* Serializable, const bool Pretty);		
};