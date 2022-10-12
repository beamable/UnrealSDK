
#pragma once

#include "CoreMinimal.h"
#include "InventoryQueryRequestBody.h"

#include "InventoryQueryRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UInventoryQueryRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize InventoryQueryRequestBody To JSON String")
	static FString InventoryQueryRequestBodyToJsonString(const UInventoryQueryRequestBody* Serializable, const bool Pretty);		
};