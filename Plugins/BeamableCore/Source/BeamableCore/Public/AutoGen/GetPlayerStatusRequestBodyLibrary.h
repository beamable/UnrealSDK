
#pragma once

#include "CoreMinimal.h"
#include "GetPlayerStatusRequestBody.h"

#include "GetPlayerStatusRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetPlayerStatusRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetPlayerStatusRequestBody To JSON String")
	static FString GetPlayerStatusRequestBodyToJsonString(const UGetPlayerStatusRequestBody* Serializable, const bool Pretty);		
};