

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfMetadataPair.h"

#include "OptionalArrayOfMetadataPairLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfMetadataPairLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfMetadataPair MakeOptionalArrayOfMetadataPair(TArray<UMetadataPair*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UMetadataPair*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfMetadataPair Conv_OptionalArrayOfMetadataPairFromValue(TArray<UMetadataPair*> Value);
};
