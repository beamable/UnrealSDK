
#pragma once

#include "CoreMinimal.h"
#include "ClearStatusRequestBody.h"

#include "ClearStatusRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UClearStatusRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ClearStatusRequestBody To JSON String")
	static FString ClearStatusRequestBodyToJsonString(const UClearStatusRequestBody* Serializable, const bool Pretty);		
};