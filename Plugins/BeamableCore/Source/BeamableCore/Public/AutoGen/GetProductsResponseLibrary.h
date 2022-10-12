
#pragma once

#include "CoreMinimal.h"
#include "GetProductsResponse.h"

#include "GetProductsResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetProductsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetProductsResponse To JSON String")
	static FString GetProductsResponseToJsonString(const UGetProductsResponse* Serializable, const bool Pretty);		
};