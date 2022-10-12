
#pragma once

#include "CoreMinimal.h"
#include "GetMailDetailsRequestBody.h"

#include "GetMailDetailsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetMailDetailsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetMailDetailsRequestBody To JSON String")
	static FString GetMailDetailsRequestBodyToJsonString(const UGetMailDetailsRequestBody* Serializable, const bool Pretty);		
};