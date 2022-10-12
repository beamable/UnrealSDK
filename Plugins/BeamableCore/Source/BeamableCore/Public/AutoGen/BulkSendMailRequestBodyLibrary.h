
#pragma once

#include "CoreMinimal.h"
#include "BulkSendMailRequestBody.h"

#include "BulkSendMailRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UBulkSendMailRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize BulkSendMailRequestBody To JSON String")
	static FString BulkSendMailRequestBodyToJsonString(const UBulkSendMailRequestBody* Serializable, const bool Pretty);		
};