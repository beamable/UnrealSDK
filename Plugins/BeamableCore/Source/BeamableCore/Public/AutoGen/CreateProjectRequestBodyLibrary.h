
#pragma once

#include "CoreMinimal.h"
#include "CreateProjectRequestBody.h"

#include "CreateProjectRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCreateProjectRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CreateProjectRequestBody To JSON String")
	static FString CreateProjectRequestBodyToJsonString(const UCreateProjectRequestBody* Serializable, const bool Pretty);		
};