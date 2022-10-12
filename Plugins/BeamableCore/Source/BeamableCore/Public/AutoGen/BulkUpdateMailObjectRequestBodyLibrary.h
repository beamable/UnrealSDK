
#pragma once

#include "CoreMinimal.h"
#include "BulkUpdateMailObjectRequestBody.h"

#include "BulkUpdateMailObjectRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UBulkUpdateMailObjectRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize BulkUpdateMailObjectRequestBody To JSON String")
	static FString BulkUpdateMailObjectRequestBodyToJsonString(const UBulkUpdateMailObjectRequestBody* Serializable, const bool Pretty);		
};