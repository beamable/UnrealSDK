
#pragma once

#include "CoreMinimal.h"
#include "GetGameRequestBody.h"

#include "GetGameRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetGameRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetGameRequestBody To JSON String")
	static FString GetGameRequestBodyToJsonString(const UGetGameRequestBody* Serializable, const bool Pretty);		
};