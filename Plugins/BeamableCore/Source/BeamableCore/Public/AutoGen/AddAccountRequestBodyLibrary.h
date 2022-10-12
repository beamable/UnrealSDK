
#pragma once

#include "CoreMinimal.h"
#include "AddAccountRequestBody.h"

#include "AddAccountRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAddAccountRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AddAccountRequestBody To JSON String")
	static FString AddAccountRequestBodyToJsonString(const UAddAccountRequestBody* Serializable, const bool Pretty);		
};