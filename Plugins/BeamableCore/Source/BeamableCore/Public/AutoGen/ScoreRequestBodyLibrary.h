
#pragma once

#include "CoreMinimal.h"
#include "ScoreRequestBody.h"

#include "ScoreRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UScoreRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ScoreRequestBody To JSON String")
	static FString ScoreRequestBodyToJsonString(const UScoreRequestBody* Serializable, const bool Pretty);		
};