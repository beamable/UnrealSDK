
#pragma once

#include "CoreMinimal.h"
#include "Promotable.h"

#include "PromotableLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPromotableLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Promotable To JSON String")
	static FString PromotableToJsonString(const UPromotable* Serializable, const bool Pretty);		
};