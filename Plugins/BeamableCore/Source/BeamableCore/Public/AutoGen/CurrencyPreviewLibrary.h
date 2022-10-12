
#pragma once

#include "CoreMinimal.h"
#include "CurrencyPreview.h"

#include "CurrencyPreviewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCurrencyPreviewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CurrencyPreview To JSON String")
	static FString CurrencyPreviewToJsonString(const UCurrencyPreview* Serializable, const bool Pretty);		
};