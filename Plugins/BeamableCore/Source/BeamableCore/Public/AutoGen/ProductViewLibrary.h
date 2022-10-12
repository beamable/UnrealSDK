
#pragma once

#include "CoreMinimal.h"
#include "ProductView.h"

#include "ProductViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UProductViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ProductView To JSON String")
	static FString ProductViewToJsonString(const UProductView* Serializable, const bool Pretty);		
};