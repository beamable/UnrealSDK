
#pragma once

#include "CoreMinimal.h"
#include "ReplaceObjectsRequestBody.h"

#include "ReplaceObjectsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UReplaceObjectsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ReplaceObjectsRequestBody To JSON String")
	static FString ReplaceObjectsRequestBodyToJsonString(const UReplaceObjectsRequestBody* Serializable, const bool Pretty);		
};