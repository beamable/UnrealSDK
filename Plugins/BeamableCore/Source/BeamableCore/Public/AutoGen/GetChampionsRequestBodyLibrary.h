
#pragma once

#include "CoreMinimal.h"
#include "GetChampionsRequestBody.h"

#include "GetChampionsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetChampionsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetChampionsRequestBody To JSON String")
	static FString GetChampionsRequestBodyToJsonString(const UGetChampionsRequestBody* Serializable, const bool Pretty);		
};