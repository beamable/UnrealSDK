
#pragma once

#include "CoreMinimal.h"
#include "PASuggestedIndex.h"

#include "PASuggestedIndexLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPASuggestedIndexLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PASuggestedIndex To JSON String")
	static FString PASuggestedIndexToJsonString(const UPASuggestedIndex* Serializable, const bool Pretty);		
};