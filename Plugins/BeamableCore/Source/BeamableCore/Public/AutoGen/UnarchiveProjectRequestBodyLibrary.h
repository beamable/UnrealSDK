
#pragma once

#include "CoreMinimal.h"
#include "UnarchiveProjectRequestBody.h"

#include "UnarchiveProjectRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UUnarchiveProjectRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize UnarchiveProjectRequestBody To JSON String")
	static FString UnarchiveProjectRequestBodyToJsonString(const UUnarchiveProjectRequestBody* Serializable, const bool Pretty);		
};