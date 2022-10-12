
#pragma once

#include "CoreMinimal.h"
#include "InventoryView.h"

#include "InventoryViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UInventoryViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize InventoryView To JSON String")
	static FString InventoryViewToJsonString(const UInventoryView* Serializable, const bool Pretty);		
};