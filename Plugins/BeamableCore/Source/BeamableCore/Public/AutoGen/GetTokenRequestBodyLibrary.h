
#pragma once

#include "CoreMinimal.h"
#include "GetTokenRequestBody.h"

#include "GetTokenRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetTokenRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetTokenRequestBody To JSON String")
	static FString GetTokenRequestBodyToJsonString(const UGetTokenRequestBody* Serializable, const bool Pretty);		
};