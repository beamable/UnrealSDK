
#pragma once

#include "CoreMinimal.h"
#include "EventScoreRequestBody.h"

#include "EventScoreRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventScoreRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventScoreRequestBody To JSON String")
	static FString EventScoreRequestBodyToJsonString(const UEventScoreRequestBody* Serializable, const bool Pretty);		
};