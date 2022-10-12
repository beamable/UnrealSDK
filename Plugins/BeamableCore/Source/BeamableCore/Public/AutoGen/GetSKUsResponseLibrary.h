
#pragma once

#include "CoreMinimal.h"
#include "GetSKUsResponse.h"

#include "GetSKUsResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSKUsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetSKUsResponse To JSON String")
	static FString GetSKUsResponseToJsonString(const UGetSKUsResponse* Serializable, const bool Pretty);		
};