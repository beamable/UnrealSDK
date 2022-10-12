
#pragma once

#include "CoreMinimal.h"
#include "ItemUpdateRequestBody.h"

#include "ItemUpdateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UItemUpdateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ItemUpdateRequestBody To JSON String")
	static FString ItemUpdateRequestBodyToJsonString(const UItemUpdateRequestBody* Serializable, const bool Pretty);		
};