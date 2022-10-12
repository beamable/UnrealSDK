
#pragma once

#include "CoreMinimal.h"
#include "UploadRequestBody.h"

#include "UploadRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UUploadRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize UploadRequestBody To JSON String")
	static FString UploadRequestBodyToJsonString(const UUploadRequestBody* Serializable, const bool Pretty);		
};