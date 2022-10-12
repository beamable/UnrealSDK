
#pragma once

#include "CoreMinimal.h"
#include "AliasAvailableRequestBody.h"

#include "AliasAvailableRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAliasAvailableRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AliasAvailableRequestBody To JSON String")
	static FString AliasAvailableRequestBodyToJsonString(const UAliasAvailableRequestBody* Serializable, const bool Pretty);		
};