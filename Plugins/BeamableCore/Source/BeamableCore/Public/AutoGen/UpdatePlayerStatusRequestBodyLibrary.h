
#pragma once

#include "CoreMinimal.h"
#include "UpdatePlayerStatusRequestBody.h"

#include "UpdatePlayerStatusRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UUpdatePlayerStatusRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize UpdatePlayerStatusRequestBody To JSON String")
	static FString UpdatePlayerStatusRequestBodyToJsonString(const UUpdatePlayerStatusRequestBody* Serializable, const bool Pretty);		
};