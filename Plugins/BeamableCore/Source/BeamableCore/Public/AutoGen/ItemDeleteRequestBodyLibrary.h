
#pragma once

#include "CoreMinimal.h"
#include "ItemDeleteRequestBody.h"

#include "ItemDeleteRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UItemDeleteRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ItemDeleteRequestBody To JSON String")
	static FString ItemDeleteRequestBodyToJsonString(const UItemDeleteRequestBody* Serializable, const bool Pretty);		
};