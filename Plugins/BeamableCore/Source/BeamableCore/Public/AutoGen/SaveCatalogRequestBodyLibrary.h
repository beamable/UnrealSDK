
#pragma once

#include "CoreMinimal.h"
#include "SaveCatalogRequestBody.h"

#include "SaveCatalogRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USaveCatalogRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SaveCatalogRequestBody To JSON String")
	static FString SaveCatalogRequestBodyToJsonString(const USaveCatalogRequestBody* Serializable, const bool Pretty);		
};