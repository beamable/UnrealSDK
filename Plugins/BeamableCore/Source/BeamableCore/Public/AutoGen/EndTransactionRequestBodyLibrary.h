
#pragma once

#include "CoreMinimal.h"
#include "EndTransactionRequestBody.h"

#include "EndTransactionRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEndTransactionRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EndTransactionRequestBody To JSON String")
	static FString EndTransactionRequestBodyToJsonString(const UEndTransactionRequestBody* Serializable, const bool Pretty);		
};