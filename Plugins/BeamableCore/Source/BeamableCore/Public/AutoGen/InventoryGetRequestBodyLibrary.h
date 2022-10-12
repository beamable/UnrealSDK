
#pragma once

#include "CoreMinimal.h"
#include "InventoryGetRequestBody.h"

#include "InventoryGetRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UInventoryGetRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize InventoryGetRequestBody To JSON String")
	static FString InventoryGetRequestBodyToJsonString(const UInventoryGetRequestBody* Serializable, const bool Pretty);		
};