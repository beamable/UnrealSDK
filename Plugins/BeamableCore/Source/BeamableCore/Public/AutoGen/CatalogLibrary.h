
#pragma once

#include "CoreMinimal.h"
#include "Catalog.h"

#include "CatalogLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCatalogLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Catalog To JSON String")
	static FString CatalogToJsonString(const UCatalog* Serializable, const bool Pretty);		
};