
#pragma once

#include "CoreMinimal.h"
#include "ListTokensRequestBody.h"

#include "ListTokensRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UListTokensRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ListTokensRequestBody To JSON String")
	static FString ListTokensRequestBodyToJsonString(const UListTokensRequestBody* Serializable, const bool Pretty);		
};