
#pragma once

#include "CoreMinimal.h"
#include "Promotion.h"

#include "PromotionLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPromotionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Promotion To JSON String")
	static FString PromotionToJsonString(const UPromotion* Serializable, const bool Pretty);		
};