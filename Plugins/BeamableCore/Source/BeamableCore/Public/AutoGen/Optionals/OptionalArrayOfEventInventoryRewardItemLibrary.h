

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfEventInventoryRewardItem.h"

#include "OptionalArrayOfEventInventoryRewardItemLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfEventInventoryRewardItemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfEventInventoryRewardItem MakeOptionalArrayOfEventInventoryRewardItem(TArray<UEventInventoryRewardItem*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UEventInventoryRewardItem*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfEventInventoryRewardItem Conv_OptionalArrayOfEventInventoryRewardItemFromValue(TArray<UEventInventoryRewardItem*> Value);
};
