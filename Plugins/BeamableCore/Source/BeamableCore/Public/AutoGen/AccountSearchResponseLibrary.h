
#pragma once

#include "CoreMinimal.h"
#include "AccountSearchResponse.h"

#include "AccountSearchResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAccountSearchResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AccountSearchResponse To JSON String")
	static FString AccountSearchResponseToJsonString(const UAccountSearchResponse* Serializable, const bool Pretty);		
};