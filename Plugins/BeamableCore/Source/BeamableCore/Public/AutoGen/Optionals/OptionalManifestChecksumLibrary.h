

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalManifestChecksum.h"

#include "OptionalManifestChecksumLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalManifestChecksumLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalManifestChecksum MakeOptionalManifestChecksum(UManifestChecksum* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ManifestChecksum To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalManifestChecksum Conv_OptionalManifestChecksumFromValue(UManifestChecksum* Value);
};
