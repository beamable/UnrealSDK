

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfCompletedStatus.h"

#include "OptionalArrayOfCompletedStatusLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfCompletedStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfCompletedStatus MakeOptionalArrayOfCompletedStatus(TArray<UCompletedStatus*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UCompletedStatus*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfCompletedStatus Conv_OptionalArrayOfCompletedStatusFromValue(TArray<UCompletedStatus*> Value);
};
