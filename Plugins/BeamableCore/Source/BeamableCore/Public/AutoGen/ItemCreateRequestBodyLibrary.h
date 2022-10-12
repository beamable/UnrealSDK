
#pragma once

#include "CoreMinimal.h"
#include "ItemCreateRequestBody.h"

#include "ItemCreateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UItemCreateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ItemCreateRequestBody To JSON String")
	static FString ItemCreateRequestBodyToJsonString(const UItemCreateRequestBody* Serializable, const bool Pretty);		
};