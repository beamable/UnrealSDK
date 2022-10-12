
#pragma once

#include "CoreMinimal.h"
#include "TransferRequestBody.h"

#include "TransferRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UTransferRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize TransferRequestBody To JSON String")
	static FString TransferRequestBodyToJsonString(const UTransferRequestBody* Serializable, const bool Pretty);		
};