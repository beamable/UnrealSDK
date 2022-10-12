

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfEventRewardObtain.h"

#include "OptionalArrayOfEventRewardObtainLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfEventRewardObtainLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfEventRewardObtain MakeOptionalArrayOfEventRewardObtain(TArray<UEventRewardObtain*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UEventRewardObtain*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfEventRewardObtain Conv_OptionalArrayOfEventRewardObtainFromValue(TArray<UEventRewardObtain*> Value);
};
