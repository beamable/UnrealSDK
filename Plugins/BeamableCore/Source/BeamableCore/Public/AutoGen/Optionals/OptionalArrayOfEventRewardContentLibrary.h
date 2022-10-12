

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfEventRewardContent.h"

#include "OptionalArrayOfEventRewardContentLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfEventRewardContentLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfEventRewardContent MakeOptionalArrayOfEventRewardContent(TArray<UEventRewardContent*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UEventRewardContent*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfEventRewardContent Conv_OptionalArrayOfEventRewardContentFromValue(TArray<UEventRewardContent*> Value);
};
