
#pragma once

#include "CoreMinimal.h"
#include "GroupSearchResponse.h"

#include "GroupSearchResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGroupSearchResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GroupSearchResponse To JSON String")
	static FString GroupSearchResponseToJsonString(const UGroupSearchResponse* Serializable, const bool Pretty);		
};