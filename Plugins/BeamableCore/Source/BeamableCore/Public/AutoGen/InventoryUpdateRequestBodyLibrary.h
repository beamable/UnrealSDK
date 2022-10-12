
#pragma once

#include "CoreMinimal.h"
#include "InventoryUpdateRequestBody.h"

#include "InventoryUpdateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UInventoryUpdateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize InventoryUpdateRequestBody To JSON String")
	static FString InventoryUpdateRequestBodyToJsonString(const UInventoryUpdateRequestBody* Serializable, const bool Pretty);		
};