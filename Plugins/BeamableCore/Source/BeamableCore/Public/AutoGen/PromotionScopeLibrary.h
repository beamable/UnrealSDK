
#pragma once

#include "CoreMinimal.h"
#include "PromotionScope.h"

#include "PromotionScopeLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPromotionScopeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PromotionScope To JSON String")
	static FString PromotionScopeToJsonString(const UPromotionScope* Serializable, const bool Pretty);		
};