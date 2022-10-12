

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalMetadataView.h"

#include "OptionalMetadataViewLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalMetadataViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalMetadataView MakeOptionalMetadataView(UMetadataView* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "MetadataView To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalMetadataView Conv_OptionalMetadataViewFromValue(UMetadataView* Value);
};
