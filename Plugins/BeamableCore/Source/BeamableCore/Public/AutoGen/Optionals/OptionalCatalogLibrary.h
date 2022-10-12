

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalCatalog.h"

#include "OptionalCatalogLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalCatalogLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalCatalog MakeOptionalCatalog(UCatalog* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Catalog To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalCatalog Conv_OptionalCatalogFromValue(UCatalog* Value);
};
