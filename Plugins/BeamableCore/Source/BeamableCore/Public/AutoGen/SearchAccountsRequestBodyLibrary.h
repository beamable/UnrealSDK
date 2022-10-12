
#pragma once

#include "CoreMinimal.h"
#include "SearchAccountsRequestBody.h"

#include "SearchAccountsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USearchAccountsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SearchAccountsRequestBody To JSON String")
	static FString SearchAccountsRequestBodyToJsonString(const USearchAccountsRequestBody* Serializable, const bool Pretty);		
};