
#pragma once

#include "CoreMinimal.h"
#include "GetProductResponse.h"

#include "GetProductResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetProductResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetProductResponse To JSON String")
	static FString GetProductResponseToJsonString(const UGetProductResponse* Serializable, const bool Pretty);		
};