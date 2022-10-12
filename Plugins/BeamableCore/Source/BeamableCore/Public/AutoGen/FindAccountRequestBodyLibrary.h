
#pragma once

#include "CoreMinimal.h"
#include "FindAccountRequestBody.h"

#include "FindAccountRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UFindAccountRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize FindAccountRequestBody To JSON String")
	static FString FindAccountRequestBodyToJsonString(const UFindAccountRequestBody* Serializable, const bool Pretty);		
};