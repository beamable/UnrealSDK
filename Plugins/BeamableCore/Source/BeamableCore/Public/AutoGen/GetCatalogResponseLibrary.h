
#pragma once

#include "CoreMinimal.h"
#include "GetCatalogResponse.h"

#include "GetCatalogResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCatalogResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetCatalogResponse To JSON String")
	static FString GetCatalogResponseToJsonString(const UGetCatalogResponse* Serializable, const bool Pretty);		
};