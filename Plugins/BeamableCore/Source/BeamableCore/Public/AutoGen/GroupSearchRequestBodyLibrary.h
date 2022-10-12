
#pragma once

#include "CoreMinimal.h"
#include "GroupSearchRequestBody.h"

#include "GroupSearchRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGroupSearchRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GroupSearchRequestBody To JSON String")
	static FString GroupSearchRequestBodyToJsonString(const UGroupSearchRequestBody* Serializable, const bool Pretty);		
};