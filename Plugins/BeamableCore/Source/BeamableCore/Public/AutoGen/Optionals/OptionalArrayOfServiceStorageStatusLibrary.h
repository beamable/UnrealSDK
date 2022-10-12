

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfServiceStorageStatus.h"

#include "OptionalArrayOfServiceStorageStatusLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfServiceStorageStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfServiceStorageStatus MakeOptionalArrayOfServiceStorageStatus(TArray<UServiceStorageStatus*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UServiceStorageStatus*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfServiceStorageStatus Conv_OptionalArrayOfServiceStorageStatusFromValue(TArray<UServiceStorageStatus*> Value);
};
